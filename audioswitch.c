void SetDefaultRecordDevice(tstring strDeviceName){
    const int BUFF_LEN = 260;
    //HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\MMDevices\Audio\Capture\{79434968-09f6-4dff-8086-c5e618b21473}\Role:0:
    //"DE 07 08 00 06 00 10 00 15 00 38 00 1E 00 48 03"
    HKEY hkCaptureDevices;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\MMDevices\\Audio\\Capture") , 0, KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_64KEY, &hkCaptureDevices);
    TCHAR lpwstrDeviceGuidKey[BUFF_LEN];
    DWORD dwDeviceGuidKeySize = BUFF_LEN;
    for(int i=0;RegEnumKeyEx(hkCaptureDevices, i, lpwstrDeviceGuidKey, &dwDeviceGuidKeySize, 0, 0, 0, 0) != ERROR_NO_MORE_ITEMS; ++i){
        dwDeviceGuidKeySize = BUFF_LEN;
        HKEY hkProps;
        RegOpenKeyEx(hkCaptureDevices, (tstring(lpwstrDeviceGuidKey) + _T("\\Properties")).c_str() , 0, KEY_READ | KEY_WOW64_64KEY, &hkProps);
        TCHAR data[BUFF_LEN];
        DWORD dwDataSize = BUFF_LEN;
        if(RegQueryValueEx(hkProps, _T("{a45c254e-df1c-4efd-8020-67d146a850e0},2"), 0, 0, (LPBYTE)data, &dwDataSize) !=  ERROR_SUCCESS){
            continue;
        } else {
            tstring strCurrentDeviceName(data);
            if(strDeviceName == strCurrentDeviceName){
                HKEY hkGuid;
                RegOpenKeyEx(hkCaptureDevices, lpwstrDeviceGuidKey , 0, KEY_READ | KEY_SET_VALUE | KEY_QUERY_VALUE | KEY_WOW64_64KEY | KEY_NOTIFY , &hkGuid);

                time_t CurrentTime;
                time(&CurrentTime);

                time_t     now = time(0);
                struct tm  tstruct;


                gmtime_s(&tstruct, &now);
                // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
                // for more information about date/time format

                char CustomRegistryDateValue[16];

                WORD year = tstruct.tm_year + 1900;
                WORD month = tstruct.tm_mon+1;
                WORD dayOfTheWeek = tstruct.tm_wday;
                WORD day = tstruct.tm_mday;
                WORD hour = tstruct.tm_hour;
                WORD minute = tstruct.tm_min;
                WORD second = tstruct.tm_sec;
                WORD millisec = 0x0;

                int k = 0;
                *((WORD*)CustomRegistryDateValue + k++) = year;
                *((WORD*)CustomRegistryDateValue + k++) = month;
                *((WORD*)CustomRegistryDateValue + k++) = dayOfTheWeek;
                *((WORD*)CustomRegistryDateValue + k++) = day;
                *((WORD*)CustomRegistryDateValue + k++) = hour;
                *((WORD*)CustomRegistryDateValue + k++) = minute;
                *((WORD*)CustomRegistryDateValue + k++) = second;
                *((WORD*)CustomRegistryDateValue + k++) = millisec;

                RegSetValueExA(hkGuid, ("Role:0"), 0, REG_BINARY, (LPBYTE)CustomRegistryDateValue, 16);
                RegSetValueExA(hkGuid, ("Role:1"), 0, REG_BINARY, (LPBYTE)CustomRegistryDateValue, 16);
                RegSetValueExA(hkGuid, ("Role:2"), 0, REG_BINARY, (LPBYTE)CustomRegistryDateValue, 16);
                RegFlushKey(hkGuid);
                RegCloseKey(hkGuid);
            }
        }
        RegCloseKey(hkProps);
    }
    RegCloseKey(hkCaptureDevices);
}
