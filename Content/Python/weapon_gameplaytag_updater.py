import os
import pathlib
import tkinter
from tkinter.filedialog import askdirectory

import unreal
from tkinter import Tk

weapon_tag_updater = None

def call_update_tags():
    global weapon_tag_updater
    if weapon_tag_updater is not None:
        weapon_tag_updater.update_tags()
    else:
        unreal.log("the global instance is NOT present")

class WeaponGameplayTagUpdater:
    def __init__(self):
        global weapon_tag_updater
        weapon_tag_updater = self

    def create_menu(self):
        menus = unreal.ToolMenus.get()

        main_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu"))

        menus.remove_menu(unreal.Name("LevelEditor.MainMenu.TpsTools"))
        menus.remove_menu(unreal.Name("LevelEditor.MainMenu.MainMenu"))

        tps_tool_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu.TpsTools"))
        if tps_tool_menu is None:
            unreal.log("TpsTool menu NOT found. Creating One.")
            tps_tool_menu = main_menu.add_sub_menu(owner=unreal.Name("LevelEditor.MainMenu"), section_name="LevelEditor",name="TpsTools",label="TpsTools")

            update_weapon_tags = unreal.ToolMenuEntry(
                name="UpdateWeaponGameplayTags",
                owner=unreal.ToolMenuOwner(unreal.Name("LevelEditor.MainMenu.TpsTools")),
                type=unreal.MultiBlockType.MENU_ENTRY,
            )
            update_weapon_tags.set_label("Update Weapon Gameplay Tags")
            update_weapon_tags.set_string_command(type=unreal.ToolMenuStringCommandType.PYTHON,custom_type="", string="import weapon_gameplaytag_updater; weapon_gameplaytag_updater.call_update_tags()")

            tps_tool_menu.add_menu_entry(section_name="Update",args=update_weapon_tags)
            menus.refresh_all_widgets()

    # Adds names of all Skeletal Mesh and Static Mesh from the supplied directory and sub directories as game play tags to the ini files
    def update_tags(self):
        Tk().withdraw()
        content_dir_path = unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_content_dir())
        content_dir_path1 = unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_content_dir())[:-9]

        directory = askdirectory(initialdir=content_dir_path, title="Select Weapon(s) Mesh Directory", mustexist=True)
        directory = directory.replace(content_dir_path, "/Game/")

        asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
        # unreal.log(f"is registry loading: {asset_registry.is_loading_assets()}")
        # unreal.log(f"has assets {asset_registry.has_assets(package_path=unreal.Name(directory), recursive=True)}")
        assets = asset_registry.get_assets_by_path(package_path=unreal.Name(directory), recursive=True,include_only_on_disk_assets=True)
        unreal.log(f"Total assets found {len(assets)}")

        ini_path = f"{unreal.Paths.project_dir()}Config/Tags"
        if os.path.isdir(ini_path):
            unreal.log("directory present. deleting ini files from the directory")
            try:
                files = os.listdir(ini_path)
                for file in files:
                    path = os.path.join(ini_path,file)
                    if os.path.isfile(path):
                        os.remove(path)
            except OSError:
                unreal.log("Error occurred while deleting ini files from Config/Tags")
        else:
            unreal.log("directory NOT present. Creating one.")
            os.makedirs(name=ini_path, mode=0o700, exist_ok=True)

        header = "[/Script/GameplayTags.GameplayTagsList]"
        for asset in assets:
            # SkeletalMesh, StaticMesh
            if asset.get_class().get_class_path_name().asset_name == "SkeletalMesh" or asset.get_class().get_class_path_name().asset_name == "StaticMesh":
            # unreal.log(f"asset is {asset.asset_name} and package path {asset.package_path} and class path name is {asset.get_class().get_class_path_name().asset_name}")
            #     unreal.log(f"{asset}")
                tag = unreal.StringLibrary.conv_name_to_string(asset.package_name).replace(f"{directory}/","").replace('/','.')
                names = tag.split('.')
                # unreal.log(tag)
                # unreal.log(names)
                ini_file_path = os.path.join(ini_path, f'{names[0]}.ini')
                if not os.path.exists(ini_file_path):
                    ini_file = open(ini_file_path, 'a')
                    ini_file.write(header)
                    ini_file.write('\n')

                ini_file = open(ini_file_path, 'a')
                tag_entry = f'GameplayTagList=(Tag="{tag}",DevComment="")'
                ini_file.write(tag_entry)
                ini_file.write('\n')
                ini_file.close() # not be ideal. but it is a tool for a sample project so good for now.

        var = tkinter.messagebox.showinfo("Import Complete", "Gameplay tags created! "
                                                             "You may need to toggle ProjectSettings>GamePlayTags>Import Tags From Config"
                                                             " to successfully import them into the project.")






