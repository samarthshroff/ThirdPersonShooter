import unreal
import sys

# Needed when working on python scripts and reload is needed without the need to restart the ue project
MODULE_NAME = "weapon_gameplaytag_updater"
if MODULE_NAME in sys.modules:
    del sys.modules[MODULE_NAME]
import weapon_gameplaytag_updater
from weapon_gameplaytag_updater import WeaponGameplayTagUpdater

MODULE_NAME = "datatables_creator"
if MODULE_NAME in sys.modules:
    del sys.modules[MODULE_NAME]
import datatables_creator
from datatables_creator import DataTablesCreator

menus = None
tps_tool_menu = None

def create_tps_tool_menu():
    global menus
    menus = unreal.ToolMenus.get()
    main_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu"))

    menus.remove_menu(unreal.Name("LevelEditor.MainMenu.TpsTools"))
    menus.remove_menu(unreal.Name("LevelEditor.MainMenu.MainMenu"))
    global tps_tool_menu
    tps_tool_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu.TpsTools"))
    if tps_tool_menu is None:
        unreal.log("TpsTool menu NOT found. Creating One.")
        tps_tool_menu = main_menu.add_sub_menu(owner=unreal.Name("LevelEditor.MainMenu"), section_name="LevelEditor",
                                               name="TpsTools", label="TpsTools")
        menus.refresh_all_widgets()

if __name__=="__main__":
    create_tps_tool_menu()
    tag_updater = WeaponGameplayTagUpdater()
    table_creator = DataTablesCreator()
    weapon_gameplaytag_updater.weapon_tag_updater.create_menu_option(menus, tps_tool_menu)
    datatables_creator.data_table_creator.create_menu_option(menus, tps_tool_menu)
