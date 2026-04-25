#include <windows.h>
#include <stdio.h>
#include <time.h>

void log_time() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULONGLONG nanoseconds = ((ULONGLONG)ft.dwHighDateTime << 32 | ft.dwLowDateTime) * 100;
    FILE *f = fopen("createprocess_bomb.log", "a");
    fprintf(f, "%llu\n", nanoseconds);
    fclose(f);
}

int main() {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    
    while (1) {
        if (CreateProcessA(path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            log_time();
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
    }
    
    return 0;
}