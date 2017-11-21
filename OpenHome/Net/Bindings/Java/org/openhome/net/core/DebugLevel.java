package org.openhome.net.core;

/**
 * Debug level constants used for calling {@link Library#setDebugLevel}.  Use {@link #intValue}
 * to get the integer bit-mask value.  These bit-mask values can be combined
 * when calling {@link Library#setDebugLevel}.
 *
 */
public enum DebugLevel {
    /**
     * Disable all messages.
     */
    None(0),

    /**
     * Enable <tt>Thread</tt> messages.
     */
    Thread(1<<0),

    /**
     * Enable <tt>Network</tt> messages.
     */
    Network(1<<1),

    /**
     * Enable <tt>Timer</tt> messages.
     */
    Timer(1<<2),

    /**
     * Enable <tt>SsdpMulticast</tt> messages.
     */
    SsdpMulticast(1<<3),

    /**
     * Enable <tt>SsdpUnicast</tt> messages.
     */
    SsdpUnicast(1<<4),

    /**
     * Enable <tt>Http</tt> messages.
     */
    Http(1<<5),

    /**
     * Enable <tt>Device</tt> messages.
     */
    Device(1<<6),

    /**
     * Enable <tt>XmlFetch</tt> messages.
     */
    XmlFetch(1<<7),

    /**
     * Enable <tt>Service</tt> messages.
     */
    Service(1<<8),

    /**
     * Enable <tt>Event</tt> messages.
     */
    Event(1<<9),

    /**
     * Enable <tt>SsdpNotifier</tt> messages.
     */
    SsdpNotifier(1<<10),

    /**
     * Enable <tt>DvInvocation</tt> messages.
     */
    DvInvocation(1<<11),

    /**
     * Enable <tt>DvEvent</tt> messages.
     */
    DvEvent(1<<12),

    /**
     * Enable <tt>DvWebSocket</tt> messages.
     */
    DvWebSocket(1<<13),

    /**
     * Enable <tt>Lpec</tt> messages.
     */
    Lpec(1<<14),

    /**
     * Enable <tt>Bonjour</tt> messages.
     */
    Bonjour(1<<15),

    /**
     * Enable <tt>DvDevice</tt> messages.
     */
    DvDevice(1<<16),

    App0(1<<17),
    App1(1<<18),
    App2(1<<19),
    App3(1<<20),
    App4(1<<21),
    App5(1<<22),
    App6(1<<23),
    App7(1<<24),
    App8(1<<25),
    App9(1<<26),
    App10(1<<27),
    App11(1<<28),
    App12(1<<29),
    App13(1<<30),
    App14(1<<31),
    App15(1<<32),
    App16(1<<33),
    App17(1<<34),
    App18(1<<35),
    App19(1<<36),
    App20(1<<37),
    App21(1<<38),
    App22(1<<39),
    App23(1<<40),
    App24(1<<41),
    App25(1<<42),
    App26(1<<43),
    App27(1<<44),
    App28(1<<45),
    App29(1<<46),
    App30(1<<47),
    App31(1<<48),
    App32(1<<49),
    App33(1<<50),
    App34(1<<51),
    App35(1<<52),
    App36(1<<53),
    App37(1<<54),
    App38(1<<55),
    App39(1<<56),
    App40(1<<57),
    App41(1<<58),
    App42(1<<59),
    App43(1<<60),
    App44(1<<61),

     /**
      * Enable <tt>CpDeviceDv</tt> messages.
      */
    CpDeviceDv(1<<62),

     /**
      * Enable <tt>AdapterChange</tt> messages.
      */
    AdapterChange(1<<63),

     /**
      * Enable all messages.
      */
    All(0xFFFFFFFFFFFFFFFFL);

    private long value;

    private DebugLevel(long value) {
        this.value = value;
    }

    /**
     * Returns the long bit-mask value for a {@link DebugLevel} enum constant.
     *
     * @return      the long bit-mask value.
     */
    public long longValue() {
        return value;
    }
}
