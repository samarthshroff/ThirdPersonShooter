import unreal
import sys

# Needed when working on python scripts and reload is needed without the need to restart the ue project
MODULE_NAME = "weapon_gameplaytag_updater"
if MODULE_NAME in sys.modules:
    del sys.modules[MODULE_NAME]
import weapon_gameplaytag_updater

from weapon_gameplaytag_updater import WeaponGameplayTagUpdater

if __name__=="__main__":
    temp = WeaponGameplayTagUpdater()
    weapon_gameplaytag_updater.weapon_tag_updater.create_menu()
