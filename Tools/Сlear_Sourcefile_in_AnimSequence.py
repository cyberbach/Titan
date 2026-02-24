import unreal

NEW_SOURCE_PATH = "AnimationToUnreal.fbx"  # ваш путь

def process_selected_anim_sequences():
    selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()
    if not selected_assets:
        unreal.log_warning("❌ Не выбрано ни одного ассета.")
        return

    for asset in selected_assets:
        if not isinstance(asset, unreal.AnimSequence):
            unreal.log(f"⏭️ Пропуск {asset.get_name()} — не Animation Sequence")
            continue

        # Вызываем метод
        method_name = 'set_anim_sequence_source_file'
        if hasattr(asset, method_name):
            method = getattr(asset, method_name)
            method(NEW_SOURCE_PATH)
        else:
            unreal.log_error(f"❌ У {asset.get_name()} нет метода '{method_name}'")
            continue

        # Сохраняем
        unreal.EditorAssetLibrary.save_asset(asset.get_path_name())

        # Читаем обратно
        import_data = asset.get_editor_property('asset_import_data')
        if import_data:
            first_file = import_data.get_first_filename()
            unreal.log(f"✅ get_first_filename() = {first_file}")
            all_files = import_data.extract_filenames()
            unreal.log(f"✅ Все файлы: {all_files}")
        else:
            unreal.log_error("❌ Нет import_data")

if __name__ == "__main__":
    process_selected_anim_sequences()