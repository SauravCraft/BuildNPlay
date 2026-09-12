\# SaveSystem Plugin



A lightweight, modular save/load framework for Unreal Engine 5 built around `UGameInstanceSubsystem`. The plugin is designed to work independently and allows other gameplay plugins (Respawn, Inventory, Quest, etc.) to participate in the save process through delegates.



\---



\# Features



\- Modular architecture

\- GameInstance Subsystem based

\- Automatic SaveGame object management

\- Custom save slots

\- Delegate-based save/load events

\- Plugin friendly

\- Easy integration with other systems

\- Supports multiple gameplay plugins



\---



\# Folder Structure



```

SaveSystem

│

├── Public

│   ├── SaveGames

│   │     SaveGameData.h

│   │

│   └── Subsystems

│         SaveManagerSubsystem.h

│

├── Private

│   ├── SaveGames

│   └── Subsystems

│

└── SaveSystem.uplugin

```



\---



\# Architecture



```

Gameplay

&#x20;   │

&#x20;   ▼

SaveManagerSubsystem

&#x20;   │

&#x20;   ├── Broadcast Save

&#x20;   │

&#x20;   ├── Respawn Plugin

&#x20;   ├── Inventory Plugin

&#x20;   ├── Quest Plugin

&#x20;   ├── Stats Plugin

&#x20;   └── Any Custom Plugin

&#x20;   │

&#x20;   ▼

SaveGameData

&#x20;   │

&#x20;   ▼

SaveGameToSlot()

```



\---



\# Save Flow



```

Player Requests Save

&#x20;       │

&#x20;       ▼

SaveManagerSubsystem::SaveGame()

&#x20;       │

&#x20;       ▼

OnGameSaved.Broadcast()

&#x20;       │

&#x20;       ├── Respawn

&#x20;       ├── Inventory

&#x20;       ├── Quest

&#x20;       └── Others

&#x20;       │

&#x20;       ▼

UGameplayStatics::SaveGameToSlot()

```



\---



\# Load Flow



```

LoadGame()

&#x20;     │

&#x20;     ▼

Load SaveGame Object

&#x20;     │

&#x20;     ▼

OnGameLoaded.Broadcast()

&#x20;     │

&#x20;     ├── Respawn

&#x20;     ├── Inventory

&#x20;     ├── Quest

&#x20;     └── Others

```



\---



\# Installation



1\. Copy the plugin into:



```

Project/Plugins/

```



2\. Enable the plugin.



3\. Rebuild the project.



\---



\# Creating Save Data



Extend `USaveGameData`.



Example:



```cpp

UPROPERTY(BlueprintReadWrite)

FTransform PlayerTransform;



UPROPERTY(BlueprintReadWrite)

float Health;



UPROPERTY(BlueprintReadWrite)

TArray<FItemData> Inventory;

```



\---



\# Saving



```cpp

USaveManagerSubsystem\* Save =

&#x20;   GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();



if (Save)

{

&#x20;   Save->SaveGame();

}

```



\---



\# Loading



```cpp

USaveManagerSubsystem\* Save =

&#x20;   GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();



if (Save)

{

&#x20;   Save->LoadGame();

}

```



\---



\# Delegates



Plugins can subscribe to save/load events.



```cpp

Save->OnGameSaved.AddUObject(

&#x20;   this,

&#x20;   \&UMySubsystem::HandleSave);



Save->OnGameLoaded.AddUObject(

&#x20;   this,

&#x20;   \&UMySubsystem::HandleLoad);

```



Example:



```cpp

void UMySubsystem::HandleSave(USaveGameData\* SaveGame)

{

&#x20;   // Write data

}



void UMySubsystem::HandleLoad(USaveGameData\* SaveGame)

{

&#x20;   // Restore data

}

```



\---



\# Save Slots



Default slot



```

SaveSlot

```



Change slot



```cpp

Save->SetSaveSlot(TEXT("MySlot"));

```



\---



\# Requirements



\- Unreal Engine 5.7+

\- C++ Project



\---



\# Integration Example



Respawn Plugin



```cpp

Save->OnGameSaved.AddUObject(

&#x20;   this,

&#x20;   \&URespawnSubsystem::HandleSave);



Save->OnGameLoaded.AddUObject(

&#x20;   this,

&#x20;   \&URespawnSubsystem::HandleLoad);

```



Inventory Plugin



```cpp

Save->OnGameSaved.AddUObject(

&#x20;   this,

&#x20;   \&UInventorySubsystem::HandleSave);



Save->OnGameLoaded.AddUObject(

&#x20;   this,

&#x20;   \&UInventorySubsystem::HandleLoad);

```



\---



\# Notes



\- SaveManagerSubsystem only manages the save process.

\- Gameplay plugins own their own save data.

\- Plugins communicate using delegates.

\- The SaveSystem plugin never needs to know about gameplay systems directly.

\- New plugins can participate in saving without modifying the SaveSystem source.



\---



\# Best Practices



\- Broadcast save delegates before calling `SaveGameToSlot()`.

\- Broadcast load delegates after loading from disk.

\- Call `LoadGame()` only after all required gameplay subsystems have initialized.

\- Keep gameplay data inside the owning subsystem.

\- Avoid direct dependencies between gameplay plugins.



\---



\# Author



Developed by \*\*Saurav Kumar\*\*



Project: \*\*Origin Framework\*\*

