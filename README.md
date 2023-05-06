# Audio Device Changer

This program allows you to change the default audio input device on Windows.

## Description

The `SetDefaultRecordDevice` function in this C program iterates through the audio capture devices in the Windows registry and finds the device with a specified name. Once the device is found, it modifies the registry values to set it as the default recording device.

## Usage

1. Compile and run the program on a Windows machine.
2. Call the `SetDefaultRecordDevice` function, passing the desired device name as a parameter.
3. The program will search for the device with the given name among the audio capture devices in the registry.
4. If the device is found, the program updates the registry values to set it as the default recording device.

## Prerequisites

- Windows operating system.
- Visual Studio or another C compiler to compile and run the program.

## Code Explanation

- The program uses the Windows registry functions (`RegOpenKeyEx`, `RegEnumKeyEx`, `RegQueryValueEx`, `RegSetValueExA`, etc.) to access and modify the registry keys related to audio capture devices.
- It iterates through the subkeys under the `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\MMDevices\Audio\Capture` registry key to find the audio devices.
- For each device, it checks if the `{a45c254e-df1c-4efd-8020-67d146a850e0},2` value exists under the `Properties` subkey. If it exists, it retrieves the current device name.
- If the current device name matches the desired device name, it opens the registry key for that device and modifies the registry values to set it as the default recording device.

## Limitations

- The program assumes the specified device name exists in the registry.
- Modifying the Windows registry should be done with caution as it can have 
