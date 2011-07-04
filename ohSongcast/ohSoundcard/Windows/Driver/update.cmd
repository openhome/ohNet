copy ohSoundcard.inf pkg\ohSoundcard.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg\ohSoundcard.sys
inf2cat.exe /driver:pkg /os:Vista_X86,Vista_X64,7_X86,7_X64 /v
SignTool sign /s PrivateCertStore pkg\ohSoundcard.cat
SignTool sign /s PrivateCertStore pkg\ohSoundcard.sys
%basedir%\tools\devcon\amd64\devcon.exe update pkg\ohSoundcard.inf {D6BAC7AB-8758-43A9-917F-D702501F4DB0}\ohSoundcard
