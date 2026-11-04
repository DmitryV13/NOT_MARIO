param(
    [string]$Version = "3.1.0",
    [Parameter(Mandatory = $true)][string]$Target
)

$ErrorActionPreference = "Stop"
$ProgressPreference = "SilentlyContinue"   # Without this, Invoke-WebRequest is very slow.
$Target = $Target.TrimEnd('\', '.')

if (Test-Path (Join-Path $Target "include\SFML")) {
    Write-Host "SFML $Version already installed at $Target"
    exit 0
}

$name = "SFML-$Version-windows-vc17-64-bit.zip"
$urls = @(
    "https://www.sfml-dev.org/files/$name",
    "https://github.com/SFML/SFML/releases/download/$Version/$name"
)

$zip = Join-Path $env:TEMP $name
$tmp = Join-Path $env:TEMP "SFML-extract-$Version"

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$ok = $false
foreach ($url in $urls) {
    try {
        Write-Host "Downloading $url ..."
        Invoke-WebRequest -Uri $url -OutFile $zip
        $ok = $true
        break
    } catch {
        Write-Host "Failed: $($_.Exception.Message)"
    }
}
if (-not $ok) { throw "Could not download SFML $Version" }

if (Test-Path $tmp) { Remove-Item $tmp -Recurse -Force }
Expand-Archive -Path $zip -DestinationPath $tmp

# Inside the archive, there is an SFML-x.y.z directory, which we locate by checking for the presence of the include directory.
$src = Get-ChildItem $tmp -Directory | Where-Object { Test-Path (Join-Path $_.FullName "include") } | Select-Object -First 1
if (-not $src) { throw "Unexpected archive layout" }

New-Item -ItemType Directory -Force -Path (Split-Path $Target) | Out-Null
if (Test-Path $Target) { Remove-Item $Target -Recurse -Force }
Move-Item $src.FullName $Target

Remove-Item $zip -Force
Remove-Item $tmp -Recurse -Force
Write-Host "SFML installed to $Target"