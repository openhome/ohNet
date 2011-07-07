
objects_topology = $(ohnetdir)CpTopology.$(objext) \
                   $(ohnetdir)CpTopology1.$(objext) \
                   $(ohnetdir)CpTopology2.$(objext) \
                   $(ohnetdir)CpTopology3.$(objext) \
                   $(ohnetdir)CpAvOpenhomeOrgProduct1.$(objext) \
                   $(ohnetdir)CpAvOpenhomeOrgVolume1.$(objext)


objects_songcast = $(objdir)Ohm.$(objext) \
                   $(objdir)OhmSender.$(objext) \
                   $(ohnetdir)CpAvOpenhomeOrgReceiver1.$(objext) \
                   $(ohnetdir)DvAvOpenhomeOrgSender1.$(objext)

headers_songcast = Ohm.h \
                   OhmSender.h

$(objdir)Ohm.$(objext) : Ohm.cpp $(headers_songcast)
	$(compiler)Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
$(objdir)OhmSender.$(objext) : OhmSender.cpp $(headers_songcast)
	$(compiler)OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp


objects_recvrmgrs = $(objdir)ReceiverManager1.$(objext) \
                    $(objdir)ReceiverManager2.$(objext) \
                    $(objdir)ReceiverManager3.$(objext)

objects_soundcard = $(objdir)ReceiverManager1.$(objext) \
                    $(objdir)ReceiverManager2.$(objext) \
                    $(objdir)ReceiverManager3.$(objext) \
                    $(objdir)Soundcard.$(objext)

headers_soundcard = ohSoundcard$(dirsep)ReceiverManager1.h \
                    ohSoundcard$(dirsep)ReceiverManager2.h \
                    ohSoundcard$(dirsep)ReceiverManager3.h \
                    ohSoundcard$(dirsep)Soundcard.h

$(objdir)ReceiverManager1.$(objext) : ohSoundcard$(dirsep)ReceiverManager1.cpp $(headers_soundcard)
	$(compiler)ReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)ReceiverManager1.cpp
$(objdir)ReceiverManager2.$(objext) : ohSoundcard$(dirsep)ReceiverManager2.cpp $(headers_soundcard)
	$(compiler)ReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)ReceiverManager2.cpp
$(objdir)ReceiverManager3.$(objext) : ohSoundcard$(dirsep)ReceiverManager3.cpp $(headers_soundcard)
	$(compiler)ReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)ReceiverManager3.cpp
$(objdir)Soundcard.$(objext) : ohSoundcard$(dirsep)Soundcard.cpp $(headers_soundcard)
	$(compiler)Soundcard.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)Soundcard.cpp


all_common : TestReceiverManager1 TestReceiverManager2 TestReceiverManager3 ZoneWatcher WavSender


TestReceiverManager1 : $(objdir)TestReceiverManager1.$(exeext)
$(objdir)TestReceiverManager1.$(exeext) : ohSoundcard$(dirsep)TestReceiverManager1.cpp $(objects_songcast) $(objects_soundcard)
	$(compiler)TestReceiverManager1.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)TestReceiverManager1.cpp
	$(link) $(linkoutput)$(objdir)TestReceiverManager1.$(exeext) $(objdir)TestReceiverManager1.$(objext) $(objects_recvrmgrs) $(objects_songcast) $(objects_topology) $(ohnetdir)$(libprefix)ohNetCore.$(libext) $(ohnetdir)$(libprefix)TestFramework.$(libext)


TestReceiverManager2 : $(objdir)TestReceiverManager2.$(exeext)
$(objdir)TestReceiverManager2.$(exeext) : ohSoundcard$(dirsep)TestReceiverManager2.cpp $(objects_songcast) $(objects_soundcard)
	$(compiler)TestReceiverManager2.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)TestReceiverManager2.cpp
	$(link) $(linkoutput)$(objdir)TestReceiverManager2.$(exeext) $(objdir)TestReceiverManager2.$(objext) $(objects_recvrmgrs) $(objects_songcast) $(objects_topology) $(ohnetdir)$(libprefix)ohNetCore.$(libext) $(ohnetdir)$(libprefix)TestFramework.$(libext)


TestReceiverManager3 : $(objdir)TestReceiverManager3.$(exeext)
$(objdir)TestReceiverManager3.$(exeext) : ohSoundcard$(dirsep)TestReceiverManager3.cpp $(objects_songcast) $(objects_soundcard)
	$(compiler)TestReceiverManager3.$(objext) -c $(cflags) $(includes) ohSoundcard$(dirsep)TestReceiverManager3.cpp
	$(link) $(linkoutput)$(objdir)TestReceiverManager3.$(exeext) $(objdir)TestReceiverManager3.$(objext) $(objects_recvrmgrs) $(objects_songcast) $(objects_topology) $(ohnetdir)$(libprefix)ohNetCore.$(libext) $(ohnetdir)$(libprefix)TestFramework.$(libext)


ZoneWatcher : $(objdir)ZoneWatcher.$(exeext)
$(objdir)ZoneWatcher.$(exeext) : ZoneWatcher$(dirsep)ZoneWatcher.cpp $(objects_songcast)
	$(compiler)ZoneWatcher.$(objext) -c $(cflags) $(includes) ZoneWatcher$(dirsep)ZoneWatcher.cpp
	$(link) $(linkoutput)$(objdir)ZoneWatcher.$(exeext) $(objdir)ZoneWatcher.$(objext) $(objects_songcast) $(ohnetdir)$(libprefix)ohNetCore.$(libext) $(ohnetdir)$(libprefix)TestFramework.$(libext)


WavSender : $(objdir)WavSender.$(exeext)
$(objdir)WavSender.$(exeext) : WavSender$(dirsep)WavSender.cpp $(objects_songcast)
	$(compiler)WavSender.$(objext) -c $(cflags) $(includes) WavSender$(dirsep)WavSender.cpp
	$(link) $(linkoutput)$(objdir)WavSender.$(exeext) $(objdir)WavSender.$(objext) $(objects_songcast) $(ohnetdir)$(libprefix)ohNetCore.$(libext) $(ohnetdir)$(libprefix)TestFramework.$(libext)


