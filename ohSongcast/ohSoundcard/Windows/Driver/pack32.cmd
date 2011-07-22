copy ohSoundcard.inf pkg32\ohSoundcard.inf
copy drmsimp\objchk_win7_x86\i386\vaddrms.sys pkg32\ohSoundcard.sys
inf2cat.exe /driver:pkg32 /os:Vista_X86,7_X86 /v
Signtool sign /a /t http://timestamp.verisign.com/scripts/timestamp.dll pkg32\ohSoundcard.cat
Signtool verify /pa /v /c pkg32\ohSoundcard.cat pkg32\ohSoundcard.sys