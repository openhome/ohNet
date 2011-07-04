copy ohSoundcard.inf pkg64\ohSoundcard.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg64\ohSoundcard.sys
inf2cat.exe /driver:pkg64 /os:Vista_X64,7_X64 /v
Signtool sign /f ohSoundcard.p12 /p basket /t http://timestamp.verisign.com/scripts/timestamp.dll pkg64\ohSoundcard.cat
Signtool sign /f ohSoundcard.p12 /p basket /t http://timestamp.verisign.com/scripts/timestamp.dll pkg64\ohSoundcard.sys
