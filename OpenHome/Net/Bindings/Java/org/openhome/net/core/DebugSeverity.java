package org.openhome.net.core;

/**
 * Debug severity constants used for calling {@link Library#setDebugSeverity}.  Use {@link #intValue}
 * to get the integer severity value.
 */
public enum DebugSeverity {
    /**
     * Disable all messages.
     */
    None(0),

    /**
     * Enable <tt>Critical</tt> messages.
     */
    Critical(1),

    /**
     * Enable <tt>Error</tt> messages.
     */
    Error(2),

    /**
     * Enable <tt>Warning</tt> messages.
     */
    Warning(3),

    /**
     * Enable <tt>Info</tt> messages.
     */
    Info(4),

    /**
     * Enable <tt>Debug</tt> messages.
     */
    Debug(5),

    /**
     * Enable <tt>Trace</tt> messages.
     */
    Trace(6);

    private int value;

    private DebugSeverity(int value) {
        this.value = value;
    }

    /**
     * Returns the integer severity value for a {@link DebugSeverity} enum constant.
     *
     * @return      the integer severity value.
     */
    public int intValue() {
        return value;
    }
}
