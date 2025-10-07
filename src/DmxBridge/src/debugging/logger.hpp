#pragma once

#ifdef DEBUG
    #define PrintDebug(parameter) Serial.print(parameter)
    #define PrintLnDebug(parameter) Serial.println(parameter)
#else
    #define PrintDebug(parameter)
    #define PrintLnDebug(parameter)
#endif

#ifdef INFO
    #define PrintInfo(parameter) Serial.print(parameter)
    #define PrintLnInfo(parameter) Serial.println(parameter)
#else
    #define PrintInfo(parameter)
    #define PrintLnInfo(parameter)
#endif
