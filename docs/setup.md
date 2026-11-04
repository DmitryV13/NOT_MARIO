## Building and SFML setup

This project uses [SFML](https://www.sfml-dev.org/). You do **not** need to download it or configure Visual Studio paths manually: everything is set up automatically on the first build.

### What to change and where

| I want to... | File | What to edit |
|--------------|------|--------------|
| Change the SFML version | `Directory.Build.props` | `<SfmlVersion>` value (e.g. `3.1.0`) |
| Change where SFML is installed | `Directory.Build.props` | `<SfmlDir>` line, or set the `SFML_DIR` environment variable |
| Change the download URL or archive type (e.g. another compiler build) | `setup_sfml.ps1` | `$name` and `$urls` variables |
| Add or remove SFML modules | `Directory.Build.props` | `<AdditionalDependencies>` in the Debug and Release blocks |
| Change which DLLs are copied to the output folder | `Directory.Build.props` | `<SfmlDlls>` masks in the `CopySfmlDlls` target |
| Change the C++ standard | `Directory.Build.props` | `<LanguageStandard>` (currently `stdcpp17`) |

**Changing the SFML version:** edit `SfmlVersion` in `Directory.Build.props`. The new version is downloaded automatically on the next build into `%USERPROFILE%\libraries\SFML-<version>`. For a different major version (e.g. 2.x), also change the DLL masks in `CopySfmlDlls` (`-3.dll` → `-2.dll`, `-d-3.dll` → `-d-2.dll`).

### Requirements

- Windows, Visual Studio 2022 or newer (workload "Desktop development with C++")
- PowerShell (included with Windows)
- Internet access on the first build

### Quick start

1. Clone the repository.
2. Open the `.sln` file in Visual Studio.
3. Select a configuration (Debug or Release, x64) and click **Build**.

On the first build, SFML is downloaded to `%USERPROFILE%\libraries\SFML-<version>` (outside the repository), the project is compiled, and the required DLLs are copied to `x64\Debug` or `x64\Release`. Subsequent builds skip the download.

### How it works

| File | Purpose |
|------|---------|
| `setup_sfml.ps1` | Downloads and extracts SFML if it is not installed yet |
| `Directory.Build.props` | Sets include/library paths, links the `.lib` files for Debug and Release, and copies DLLs after the build |

SFML settings in the project properties (include directories, library directories, `Additional Dependencies`, post-build copy) do not need to be set manually.

### Linked modules

`system`, `window`, `graphics`, `audio`, `network`. Debug uses libraries with the `-d` suffix (`sfml-graphics-d.lib`, etc.).

### Using an existing SFML installation

Set the `SFML_DIR` environment variable to the SFML root folder (the one containing `include`, `lib` and `bin`), for example:

```
C:\libraries\SFML-3.1.0
```

Restart Visual Studio afterwards. No download will be performed in this case.

### Installing SFML manually

```
powershell -ExecutionPolicy Bypass -File setup_sfml.ps1 -Version 3.1.0 -Target "%USERPROFILE%\libraries\SFML-3.1.0"
```

### Troubleshooting

- **SFML headers are underlined before the first build.** IntelliSense picks them up after the first successful build.
- **SFML download failed.** Check your internet connection, or download `SFML-<version>-windows-vc17-64-bit.zip` from the SFML website and extract it into the folder that `SFML_DIR` points to.
- **DLL copy error.** Make sure `<SFML_DIR>\bin` contains `sfml-*-3.dll` (and `sfml-*-d-3.dll` for Debug).
- **Duplicate paths or linker warnings.** Remove any old manual SFML settings from the project properties.
- **Multiple projects in the solution.** On the very first build the script may start in parallel. Build one project first, or run the script manually (see above).