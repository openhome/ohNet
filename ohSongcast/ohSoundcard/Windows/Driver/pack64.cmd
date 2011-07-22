copy ohSoundcard.inf pkg64\ohSoundcard.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg64\ohSoundcard.sys
Signtool sign /v /a /ac gsrootr1.crt /t http://timestamp.verisign.com/scripts/timestamp.dll pkg64\ohSoundcard.sys
inf2cat.exe /driver:pkg64 /os:Vista_X64,7_X64 /v
Signtool sign /v /a /ac gsrootr1.crt /t http://timestamp.verisign.com/scripts/timestamp.dll pkg64\ohSoundcard.cat
Signtool verify /pa /v /c pkg64\ohSoundcard.cat pkg64\ohSoundcard.sys
Signtool verify /kp /v /c pkg64\ohSoundcard.cat pkg64\ohSoundcard.sys