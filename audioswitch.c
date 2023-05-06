#include <Windows.h>
#include <tchar.h>
#include <string>
#include <ctime>

// Function to set the default audio recording device on Windows
void SetDefaultRecordDevice(const std::wstring& strDeviceName) {
    const int BUFF_LEN = 260;
    
    // Open the registry key for capturing audio devices
    HKEY hkCaptureDevices;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\MMDevices\\Audio\\Capture"), 0, KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY, &hkCaptureDevices);
    
    TCHAR lpwstrDeviceGuidKey[BUFF_LEN];
    DWORD dwDeviceGuidKeySize = BUFF_LEN;
    
    // Enumerate through each subkey (audio device) under the capture devices key
    for (int i = 0; RegEnumKeyEx(hkCaptureDevices, i, lpwstrDeviceGuidKey, &dwDeviceGuidKeySize, 0, 0, 0, 0) != ERROR_NO_MORE_ITEMS; ++i) {
        dwDeviceGuidKeySize = BUFF_LEN;
        
        HKEY hkProps;
        // Open the "Properties" subkey of the current audio device
        RegOpenKeyEx(hkCaptureDevices, (std::wstring(lpwstrDeviceGuidKey) + _T("\\Properties")).c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hkProps);
        
        TCHAR data[BUFF_LEN];
        DWORD dwDataSize = BUFF_LEN;
        
        // Check if the "{a45c254e-df1c-4efd-8020-67d146a850e0},2" value exists under the "Properties" subkey
        if (RegQueryValueEx(hkProps, _T("{a45c254e-df1c-4efd-8020-67d146a850e0},2"), 0, 0, (LPBYTE)data, &dwDataSize) != ERROR_SUCCESS) {
            // If the value doesn't exist, continue to the next audio device
            continue;
        }
        else {
            std::wstring strCurrentDeviceName(data);
            
            // Check if the current audio device matches the desired device name
            if (strDeviceName == strCurrentDeviceName) {
                HKEY hkGuid;
                // Open the current audio device's registry key
                RegOpenKeyEx(hkCaptureDevices, lpwstrDeviceGuidKey, 0, KEY_READ | KEY_SET_VALUE | KEY_QUERY_VALUE | KEY_WOW64_64KEY | KEY_NOTIFY, &hkGuid);

                // Get the current time
                time_t now = time(0);
                struct tm tstruct;
                
                // Convert the current time to a struct tm
                gmtime_s(&tstruct, &now);

                // Extract individual date/time components
                WORD year = tstruct.tm_year + 1900;
                WORD month = tstruct.tm_mon + 1;
                WORD dayOfTheWeek = tstruct.tm_wday;
                WORD day = tstruct.tm_mday;
                WORD hour = tstruct.tm_hour;
                WORD minute = tstruct.tm_min;
                WORD second = tstruct.tm_sec;
                WORD millisec = 0x0;

                // Create a binary value containing the date/time components
                int k = 0;
                WORD CustomRegistryDateValue[8];
                CustomRegistryDateValue[k++] = year;
                CustomRegistryDateValue[k++] = month;
                CustomRegistryDateValue[k++] = dayOfTheWeek;

}
