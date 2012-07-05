#
# Regular cron jobs for the ohnet package
#
0 4	* * *	root	[ -x /usr/bin/ohnet_maintenance ] && /usr/bin/ohnet_maintenance
