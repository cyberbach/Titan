# 🎮 Unreal Engine C++ Style Guide (Monsters On Titan)

**Версия:** 1.2  
**Назначение:** Обязательные и рекомендуемые правила оформления кода.  
**Аудитория:** Разработчики и AI‑ассистенты.

---

## 🔹 Общий формат правил

Каждое правило имеет:
- **ID** – уникальный код.
- **Severity** – `error` (строго), `warning` (рекомендация), `suggestion` (желательно).
- **Scope** – область применения.
- **Описание** – кратко.
- **Примеры** – ✅ правильно / ❌ неправильно.

**При генерации кода строго соблюдать `error`; `warning` – по возможности.**

---

## 1. 📁 Файлы и `generated.h`

**FILES-001** (error)  
**Scope:** любой `.h` с `UCLASS/USTRUCT/UENUM/UINTERFACE`  
**Правило:** Имя файла должно точно совпадать с именем в `#include "...generated.h"`.  

✅ **Правильно:**  
`ItemType.h` → `#include "ItemType.generated.h"`

❌ **Неправильно:**  
`ItemType.h` → `#include "WeaponType.generated.h"`

---

## 2. 💬 Комментарии

**COMMENTS-001** (error)  
**Scope:** `.h` файлы с `UCLASS/USTRUCT/UENUM`  
**Правило:** Над классом добавить комментарий с названием класса **без префикса** (A, U, F и т.д.) и с пробелами между словами. Для объявлений функций комментарии **НЕ нужны**.

✅ **Правильно:**
```cpp
//////////////////////////////////////////////////////////////////////////
// T Player Character

UCLASS()
class ATPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATPlayerCharacter();
    virtual void BeginPlay() override;
};
```

❌ **Неправильно:** комментарии над каждым методом в .h файле.

---

**COMMENTS-002** (error)  
**Scope:** `.cpp` файлы с реализациями функций  
**Правило:** Каждая функция начинается с комментария `////////// // Имя Функции`.

✅ **Правильно:**
```cpp
//////////////////////////////////////////////////////////////////////////
// Begin Play

void ATPlayerCharacter::BeginPlay()
{
    ...
}
```

❌ **Неправильно:** без комментария.

---

**COMMENTS-003** (error)  
**Scope:** `.h` файлы с макросами перед `UCLASS/USTRUCT`  
**Правило:** **Не трогать и не удалять** макросы над `UCLASS`/`USTRUCT`.

✅ **Правильно:**
```cpp
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
        ...

//////////////////////////////////////////////////////////////////////////
// UTAttributeSet

UCLASS()
class UTAttributeSet : public UAttributeSet
```

---

**COMMENTS-004** (error)  
**Scope:** `.cpp` файлы  
**Правило:** Комментарий с названием класса добавлять **только если в файле есть реализации функций**. Если файл содержит только `#include` — не добавлять.

✅ **Правильно:**
```cpp
// TAttributeSet.cpp — пустой
#include "GAS/TAttributeSet.h"
```

```cpp
// TAbilitySystemComponent.cpp — есть функции
#include "GAS/TAbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// Some Function

void UTAbilitySystemComponent::SomeFunction() { ... }
```

❌ **Неправильно:** без комментария.

---

**COMMENTS-004** (error)
**Scope:** `.h` файлы с макросами перед `UCLASS/USTRUCT`  
**Правило:** **Не трогать и не удалять** макросы, расположенные над `UCLASS`/`USTRUCT`. Оставлять как есть.

✅ **Правильно:**
```cpp
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//////////////////////////////////////////////////////////////////////////
// UTAttributeSet

UCLASS()
class UTAttributeSet : public UAttributeSet
```

---

**COMMENTS-005** (error)  
**Scope:** `.cpp` файлы  
**Правило:** Комментарий с названием класса добавлять **только если в файле есть реализации функций**. Если файл содержит только `#include` — не добавлять.

✅ **Правильно:**
```cpp
// TAttributeSet.cpp — пустой или только с include
#include "GAS/TAttributeSet.h"
```

```cpp
// TAbilitySystemComponent.cpp — есть функции
//////////////////////////////////////////////////////////////////////////
// UTAbilitySystemComponent

#include "GAS/TAbilitySystemComponent.h"

void UTAbilitySystemComponent::SomeFunction() { ... }
```

---

## 2a. 📐 Форматирование

**LAYOUT-001** (error)  
**Scope:** `.h` файлы с классами  
**Правило:** Перед модификаторами доступа `private:`/`protected:`/`public:` должна быть **ровно 1 пустая строка**.

✅ **Правильно:**
```cpp
UCLASS()
class ATPlayerCharacter : public ATCharacter
{
    GENERATED_BODY()

public:
    ATPlayerCharacter();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    int32 Value;
};
```

❌ **Неправильно:**
```cpp
UCLASS()
class ATPlayerCharacter : public ATCharacter
{
    GENERATED_BODY()
public:   // нет пустой строки
    ATPlayerCharacter();
};
```

---

**LAYOUT-002** (error)  
**Scope:** `.h` файлы с `generated.h`  
**Правило:** `#include "...generated.h"` должен быть **последним** в списке инклюдов.

✅ **Правильно:**
```cpp
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"
```

❌ **Неправильно:**
```cpp
#include "TCharacter.generated.h"  // не на месте
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
```

---

**LAYOUT-003** (error)  
**Scope:** все `.cpp` и `.h` файлы  
**Правило:** Между верхним комментарием (`// Created by ...`) и первым `#include` должна быть **ровно 1 пустая строка**.

✅ **Правильно:**
```cpp
// Created by Andrey cb Mikheev

#include "CoreMinimal.h"
```

❌ **Неправильно:**
```cpp
// Created by Andrey cb Mikheev


#include "CoreMinimal.h"  // две пустые строки
```

```cpp
// Created by Andrey cb Mikheev
#include "CoreMinimal.h"  // нет пустой строки
```

---

## 3. 🧱 Структуры (`USTRUCT`)

**STRUCT-001** (error)  
**Scope:** любая `USTRUCT`  
**Правило:** Каждая структура в отдельном файле.  
- Имя файла – **без префикса `F`** (например `CharacterData.h`).  
- Путь: `…/Structs/ИмяБезПрефикса.h`.  

✅ **Правильно:**  
`Character/Structs/CharacterData.h` – содержит `FCharacterData`.

❌ **Неправильно:**  
- файл в корне,  
- имя `FCharacterData.h`,  
- объявление в чужом файле.

---

**STRUCT-002** (warning)  
**Scope:** все `USTRUCT`, особенно используемые в `TArray` / реплицируемые  
**Правило:** Поля сортируются **по убыванию выравнивания (`alignof`)**.  
**Порядок:**  
1. Указатели, `UObject*`, `FName`, `FString` (8 байт)  
2. `double`, `int64` (8)  
3. `float`, `int32`, `FVector`, `FRotator` (4)  
4. `int16`, `uint16` (2)  
5. `bool`, `uint8`, `enum class` (1) – группировать в конце.

✅ **Правильно:** крупные поля первыми, мелкие вместе.  
❌ **Неправильно:** случайный порядок → избыточный паддинг.

---

## 4. 🔢 Перечисления (`UENUM`)

**ENUM-001** (error)  
**Scope:** любое `UENUM`  
**Правило:** Каждое перечисление в отдельном файле.  
- Имя файла – **без префикса `E`** (например `ItemType.h`).  
- Путь: `…/Enums/ИмяБезПрефикса.h`.  

---

**ENUM-002** (error)  
**Scope:** любое `UENUM`  
**Правило:**
- Каждый элемент с префиксом из заглавных букв имени (для `EItemType` → `EIT_`).  
- **Обязательно** наличие элемента `ИМЯ_MAX` в конце.  

✅ **Правильно:**
```cpp
UENUM(BlueprintType)
enum class EItemType : uint8
{
    EIT_None        UMETA(DisplayName = "None"),
    EIT_Weapon      UMETA(DisplayName = "Weapon"),
    ...
    EIT_MAX         UMETA(DisplayName = "MAX")
};
```

❌ **Неправильно:** отсутствие префикса, нет `MAX`.

---

## 5. 🚫 Запрет forward‑declaration в файлах с `generated.h`

**FORWARD-001** (error)  
**Scope:** файлы, содержащие `#include "...generated.h"`  
**Правило:** **Не использовать** `class X;`. **Всегда включать** полный заголовок.  

✅ **Правильно:**
```cpp
#include "Weapon/Structs/DamageModifierEntry.h"
#include "WeaponBuff.generated.h"
```

❌ **Неправильно:**
```cpp
#include "WeaponBuff.generated.h"
class DamageModifierEntry;
```

---

## 6. ⚙️ Инициализация полей

**INIT-001** (error)  
**Scope:** поля классов и структур  
**Правило:** Только uniform initialization `{}`, **никогда `=`**.  

✅ **Правильно:**
```cpp
int32 Level{0};
bool bFlag{true};
FName Tag{FName("Tag")};
```

❌ **Неправильно:**
```cpp
int32 Level = 0;
bool bFlag = true;
```

---

**INIT-002** (error)  
**Scope:** список инициализации конструктора  
**Правило:** Везде `{}`, **не `()`**.  

✅ **Правильно:**
```cpp
FWeaponData()
    : WeaponID{NAME_None}
    , BaseDamage{10.0f}
    , WeaponMesh{nullptr}
{}
```

❌ **Неправильно:**
```cpp
: WeaponID(NAME_None)
```

---

## 7. 📡 Репликация

**REPL-001** (error)  
**Scope:** `UPROPERTY(Replicated)` / `ReplicatedUsing`  
**Правило:** `TMap` **не реплицируется**. Используйте `TArray<TPair<>>` или ручную синхронизацию.  

✅ **Правильно:**
```cpp
UPROPERTY(Replicated)
TArray<FInventoryItem> Items;
```

❌ **Неправильно:**
```cpp
UPROPERTY(Replicated)
TMap<FName, int32> Counts;
```

---

## 8. 🔤 `FText` – инициализация

**TEXT-001** (error)  
**Scope:** любая переменная `FText`  
**Правило:** Пустой `FText` – **значение по умолчанию** `{}` или `FText::GetEmpty()`.  
**`NAME_None` НЕДОПУСТИМ** – нет неявного преобразования.  

✅ **Правильно:**
```cpp
FText CharacterName{};
FText Description{FText::GetEmpty()};
```

❌ **Неправильно:**
```cpp
FText Name{NAME_None};
FText Name{FText::FromString(TEXT(""))};
```

---

## 9. 🏷️ `FName` – инициализация

**FNAME-001** (warning)  
**Scope:** создание `FName` из строкового литерала  
**Правило:** Предпочитать `FName("...")` без макроса `TEXT()`.  

✅ **Правильно:**
```cpp
WeaponSlots.Add(FName("Primary"));
```

❌ **Неправильно (допустимо, но не рекомендуется):**
```cpp
WeaponSlots.Add(FName(TEXT("Primary")));
```

---

## 10. 🧩 Ограничения на типы в `TMap`

**MAP-001** (warning)  
**Scope:** объявление переменной типа `TMap`  
**Правило:** Избегайте использования `TMap` с **сырыми указателями на `UObject`** в качестве ключа или значения, а также с **другими контейнерами** (например `TArray`) в качестве значения. Такие конструкции могут вызывать проблемы с репликацией, сборкой мусора и производительностью.  

✅ **Правильно:**
```cpp
TMap<FName, int32>          // примитивные типы
TMap<int32, FString>        // структуры без UObject
```

❌ **Неправильно:**
```cpp
TMap<AShooterCharacter*, float>          // сырой указатель
TMap<FName, TArray<int32>>              // контейнер в значении
TMap<TObjectPtr<AActor>, FQuestData>   // умный указатель (не реплицируется, но для локальных данных допустимо с осторожностью)
```

---

## ✅ Сводка severity

| Severity | Правила |
|----------|--------|
| `error`  | FILES-001, COMMENTS-001/002/003/004, LAYOUT-001/002/003, STRUCT-001, ENUM-001/002, FORWARD-001, INIT-001/002, REPL-001, TEXT-001 |
| `warning`| STRUCT-002, FNAME-001, MAP-001 |

---

**Документ актуален.**  
© 2026 Monsters On Titan Team.