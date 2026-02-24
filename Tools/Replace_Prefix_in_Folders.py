import unreal

# ============================================
# ⚙️ НАСТРОЙКИ (меняйте здесь)
# ============================================
OLD_PREFIX = "SHOOTERCORE_"   # Префикс, который нужно заменить
NEW_PREFIX = "AS_Zombie3_"               # Новый префикс (пустая строка = удалить старый)
# ============================================

def normalize_asset_path(path):
    """Убирает виртуальный корень /All из пути, оставляя реальный корень (/Game, /Plugins и т.д.)."""
    if path.startswith("/All"):
        parts = path.split('/')
        if len(parts) > 2:
            return '/' + '/'.join(parts[2:])
    return path

def get_package_info(asset_path):
    """
    Из полного пути ассета (например, '/Game/Folder/Package.Package' или '/Game/Folder/Package')
    возвращает кортеж: (родительская_папка, имя_пакета, путь_пакета_для_rename).
    """
    asset_path = normalize_asset_path(asset_path)
    
    # Отделяем суффикс объекта (если есть)
    if '.' in asset_path:
        package_path, _ = asset_path.split('.', 1)
    else:
        package_path = asset_path

    # Имя пакета — последний сегмент пути
    package_name = package_path.split('/')[-1]
    # Папка, в которой лежит пакет
    parent_folder = '/'.join(package_path.split('/')[:-1])
    return parent_folder, package_name, package_path

def main():
    # 1. Получаем выделенные в Content Browser папки
    folders = unreal.EditorUtilityLibrary.get_selected_folder_paths()
    if not folders:
        unreal.log_warning("❌ Не выделено ни одной папки! Сначала выберите папки в Content Browser.")
        return

    renamed_count = 0
    skipped_count = 0
    error_count = 0

    for folder in folders:
        # Нормализуем путь папки (убираем /All)
        norm_folder = normalize_asset_path(folder)
        unreal.log(f"📁 Обрабатывается папка: {folder} -> {norm_folder}")

        # Получаем все ассеты внутри папки (рекурсивно, без учёта самих папок)
        asset_paths = unreal.EditorAssetLibrary.list_assets(norm_folder, recursive=True, include_folder=False)
        if not asset_paths:
            unreal.log(f"   Папка пуста или не содержит ассетов: {norm_folder}")
            continue

        for asset_path in asset_paths:
            # Получаем информацию о пакете (не загружая ассет!)
            parent, old_name, package_path = get_package_info(asset_path)

            # Проверяем, нужно ли переименовывать (используем OLD_PREFIX)
            if not old_name.startswith(OLD_PREFIX):
                skipped_count += 1
                continue

            # Формируем новое имя: заменяем старый префикс на новый
            new_name = old_name.replace(OLD_PREFIX, NEW_PREFIX, 1)
            new_package_path = f"{parent}/{new_name}"

            # Переименовываем пакет (обновляет все ссылки автоматически)
            success = unreal.EditorAssetLibrary.rename_asset(package_path, new_package_path)
            if success:
                renamed_count += 1
                unreal.log(f"   ✅ {old_name} -> {new_name}")
            else:
                error_count += 1
                unreal.log_error(f"   ❌ Не удалось переименовать {old_name} (возможно, имя уже занято)")

    # Итоговый отчёт
    unreal.log(f"\n🎉 Работа завершена!")
    unreal.log(f"   Переименовано: {renamed_count}")
    unreal.log(f"   Пропущено (нет префикса '{OLD_PREFIX}'): {skipped_count}")
    unreal.log(f"   Ошибок: {error_count}")

if __name__ == "__main__":
    main()