# CPP Study
- - -

- Croee Platform용 코드 공부를 위한 저장소 입니다.

- - -

## 서버 정보
| 장비명 | 아키텍처 | 운영체제 (OS)           | 비고      |
| :--- | :--- |:--------------------|:--------|
| **PC1** | x86 | Ubuntu 24.04 Server | RTX3090 |
| **PC2** | x86 | Windows 10          | RTX2070 |
| **MacStudio** | Arm | macOS 26.0 | M4_MAX  |
| **JetsonThor** | Arm | JetPack 7.1         | Soon    |

- - -

## 툴체인 파일 및 플랫폼 매크로
툴체인 파일은 `cmake/toolchain` 폴더에 플랫폼/아키텍처 정보를 포함한 표준 이름으로 위치
예시:
- `linux-x86_64.cmake`          -- Ubuntu x86_64 (PLATFORM_ID=linux-x86_64, macro: `PLATFORM_LINUX_X86_64`)
- `windows-x86_64-msvc.cmake`  -- Windows x86_64 (MSVC) (macro: `PLATFORM_WINDOWS_X86_64_MSVC`)
- `darwin-arm64.cmake`         -- macOS arm64 (macro: `PLATFORM_DARWIN_ARM64`)
- `jetson-thor-arm64.cmake`    -- JetsonThor board (macro: `PLATFORM_JETSON_THOR_ARM64`)

```cpp
#ifdef PLATFORM_DARWIN_ARM64
// macOS arm64 전용 최적화
#elif defined(PLATFORM_LINUX_X86_64)
// Linux x86_64 전용
#endif
```
