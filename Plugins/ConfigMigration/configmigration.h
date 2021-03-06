#ifndef CONFIGMIGRATION_H
#define CONFIGMIGRATION_H

#include "configmigration_global.h"
#include "plugins/generalpurposeplugin.h"
#include "plugins/genericplugin.h"
#include "configmigrationitem.h"
#include "config_builder.h"
#include <QList>

class Db;

CFG_CATEGORIES(ConfigMigration,
    CFG_CATEGORY(CfgMigration,
        CFG_ENTRY(bool, Migrated, false);
    )
)

class CONFIGMIGRATIONSHARED_EXPORT ConfigMigration : public GenericPlugin, public GeneralPurposePlugin
{
        Q_OBJECT
        SQLITESTUDIO_PLUGIN("configmigration.json")

    public:
        ConfigMigration();

        bool init();
        void deinit();

        QList<ConfigMigrationItem*> getItemsToMigrate() const;

        Db* getOldCfgDb() const;

    private:
        QString findOldConfig();
        bool checkOldDir(const QString& dir, QString& output);
        QList<ConfigMigrationItem*> findItemsToMigrate();

        static const constexpr char* ACTION_LINK = "migrateOldConfig";

        Db* db = nullptr;
        QList<ConfigMigrationItem*> itemsToMigrate;
        CFG_LOCAL_PERSISTABLE(ConfigMigration, cfg)

    private slots:
        void linkActivated(const QString& link);
};

#endif // CONFIGMIGRATION_H
