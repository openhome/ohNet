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
     * Enable <tt>Trace</tt> messages.
     */
    Trace(1<<1),

    /**
     * Enable <tt>Thread</tt> messages.
     */
    Thread(1<<2),

    /**
     * Enable <tt>Network</tt> messages.
     */
    Network(1<<3),

    /**
     * Enable <tt>Timer</tt> messages.
     */
    Timer(1<<4),

    /**
     * Enable <tt>SsdpMulticast</tt> messages.
     */
    SsdpMulticast(1<<5),

    /**
     * Enable <tt>SsdpUnicast</tt> messages.
     */
    SsdpUnicast(1<<6),

    /**
     * Enable <tt>Http</tt> messages.
     */
    Http(1<<7),

    /**
     * Enable <tt>Device</tt> messages.
     */
    Device(1<<8),

    /**
     * Enable <tt>XmlFetch</tt> messages.
     */
    XmlFetch(1<<9),

    /**
     * Enable <tt>Service</tt> messages.
     */
    Service(1<<10),

    /**
     * Enable <tt>Event</tt> messages.
     */
    Event(1<<11),

    /**
     * Enable <tt>Topology</tt> messages.
     */
    Topology(1<<12),

    /**
     * Enable <tt>DvInvocation</tt> messages.
     */
    DvInvocation(1<<13),

    /**
     * Enable <tt>DvEvent</tt> messages.
     */
    DvEvent(1<<14),

    /**
     * Enable <tt>DvWebSocket</tt> messages.
     */
    DvWebSocket(1<<15),
    /**
     * Enable <tt>Bonjour</tt> messages.
     */
    Bonjour(1<<17),

    /**
     * Enable <tt>DvDevice</tt> messages.
     */
    DvDevice(1<<18),

    App0(1<<20),
    App1(1<<21),
    App2(1<<22),
    App3(1<<23),
    App4(1<<24),
    App5(1<<25),
    App6(1<<26),
    App7(1<<27),
    App8(1<<28),
    App9(1<<29),

    /**
     * Enable <tt>Error</tt> messages.
     */
    Error(1<<30),

    /**
     * Enable all messages.
     */
    All(0x7FFFFFFF),

    /**
     * Enable <tt>Verbose</tt> messages.
     */
    Verbose(0x80000000);

    private int value;

    private DebugLevel(int value) {
        this.value = value;
    }

    /**
     * Returns the integer bit-mask value for a {@link DebugLevel} enum constant.
     *
     * @return      the integer bit-mask value.
     */
    public int intValue() {
        return value;
    }
}
