# Group_2
New routing algorithm in NoC

In Linux OS
open terminal

cd 'nirgam 2.1'

Before run execute file 'nirgam', we need set environment variable.
The command is as below:

export SYSTEMC_HOME=/usr/local/systemc-2.3.1 (path of systemC library)
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
export SC_SIGNAL_WRITE_CHECK=DISABLE

Then we can run executable file 'nirgam'.The command is as below:

./nirgam

We can edit nirgam.config in $nirgam 2.1/config to change the router.
Change the parameter RT_ALGO.
For example:
RT_ALGO XY

You can choose the router among {
	XY,
	OE,
	QRT,
	DYAD,
	MAXY,
	FTXY,
	PROM,
	ER,
	NAH,
	BNAH,
	MR
}
