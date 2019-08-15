Name "Bomberguy Installer"

OutFile "bomberguy_install.exe"

; The default installation directory
InstallDir $PROGRAMFILES\bomberguy

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\bomberguy" "Install_Dir"

LicenseText "License"
LicenseData "COPYING"

;--------------------------------
; Pages

Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Bomberguy (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "src/bomberguy.exe"
  File "COPYING"
  File "README"
  File "AUTHORS"
  File "ChangeLog"
  File "lib/jpeg.dll"
  File "lib/libpng1.dll"
  File "lib/SDL.dll"
  File "lib/SDL_image.dll"
  File "lib/SDL_mixer.dll"
  File "lib/zlib.dll"
  SetOutPath "$INSTDIR\data"
  File /r "data/"
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\bomberguy "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bomberguy" "DisplayName" "Bomberguy"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bomberguy" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bomberguy" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bomberguy" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Bomberguy"
  CreateShortCut "$SMPROGRAMS\Bomberguy\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Bomberguy\Bomberguy.lnk" "$INSTDIR\bomberguy.exe" "" "$INSTDIR\bomberguy.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bomberguy"
  DeleteRegKey HKLM SOFTWARE\bomberguy

  ; Remove files and uninstaller
  Delete $INSTDIR\bomberguy.exe
  Delete $INSTDIR\AUTHORS
  Delete $INSTDIR\ChangeLog
  Delete $INSTDIR\COPYING
  Delete $INSTDIR\README
  Delete $INSTDIR\uninstall.exe
  Delete $INSTDIR\jpeg.dll
  Delete $INSTDIR\libpng1.dll
  Delete $INSTDIR\SDL.dll
  Delete $INSTDIR\SDL_image.dll
  Delete $INSTDIR\SDL_mixer.dll
  Delete $INSTDIR\zlib.dll
  
  RMDir /r $INSTDIR\data
  
  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\bomberguy\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\bomberguy"
  RMDir /r "$INSTDIR"
  Delete /REBOOTOK "$INSTDIR"

SectionEnd
