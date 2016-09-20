#ifndef DEFINE
#define DEFINE


namespace define{


    static const double PI = 3.1415926535897932384626433832795;



    // condition of experiment
    static const unsigned int MAX_COUNT = 500001;	// simulation count
    // cut of frec. of low pass filter<tracking error>(rad/s)
    // if set value zero,lpf is disenabled.

    static	const double CUTOFF_FREC_X	= 0;	//

    static const double CUTOFF_FREC_Y1	= 0,
                        CUTOFF_FREC_Y2	= 0,
                        CUTOFF_FREC_Z	= 0,
                        CUTOFF_FREC_C	= 0,
                        CUTOFF_FREC_A1	= 0,
                        CUTOFF_FREC_A2	= 0;

    // parameter of reference
    static const double RADIUS			= 0.01;					// m
    static const double OMG				= (2*PI) / 1 * 1.00;					// rad/sec
    static const double SPEEDZ			= 0;	// m/sec
    static const double INIT_POS_X		= 0,					// initial position(m,rad)
                        INIT_POS_Y1		= 0,/*0.01, -0.01,*/	//
                        INIT_POS_Y2		= INIT_POS_Y1,
                        INIT_POS_Z		= 0,/*-0.01, -0.010,*/
                        INIT_ANGLE_C	= 0,
                        INIT_ANGLE_A1	= 0,
                        INIT_ANGLE_A2	= INIT_ANGLE_A1,

                        INIT5_POS_X		= 0,					// initial position(m,rad)
                        INIT5_POS_Y1		= 0.01,/*0.01, -0.01,*/	//
                        INIT5_POS_Y2		= INIT5_POS_Y1,
                        INIT5_POS_Z		= 0,/*-0.01, -0.010,*/
                        INIT5_ANGLE_C	= 0,
                        INIT5_ANGLE_A1	= 0,
                        INIT5_ANGLE_A2	= INIT5_ANGLE_A1;
    //static double NumI = 0;

    // hardware data
    static const double DISTANCE_FROM_A_TO_C_AXIS	= 0;//4.5/1000;				// distance from center of a-axis to surface of c-axis[meter]
    static const double OFFSET_BETWEEN_COORDINATE	= 0;					// distance between the rotary drive coordinate sys.[meter]
    static const unsigned int NUM_LINEAR_ACTUATOR	= 4;					// number of linear motor
    static const unsigned int NUM_ROTATION_ACTUATOR	= 3;					// number of motor

    static const unsigned int NUM_ACTUATOR			= NUM_ROTATION_ACTUATOR + NUM_LINEAR_ACTUATOR;
                                                                            // number of actuator
    static const unsigned int NUM_COUNTER			= NUM_ACTUATOR;			// number of counter ch.
    static const unsigned int DIMENSION				= 3;					// 3-dimension
    static const unsigned int NUM_DOF				= 5;					// 5-degrees of freedom
    static const double SAMPLING_TIME				= 0.0002;				// sec
    static const double RESONATE_LINER_ENC_X		= (1.0/10000000.0);		// m/pulse
    static const double RESONATE_LINER_ENC_Y1		= (1.0/10000000.0);		// m/pulse
    static const double RESONATE_LINER_ENC_Y2		= (1.0/10000000.0);		// m/pulse
    static const double RESONATE_LINER_ENC_Z		= (1.0/10000000.0);		// m/pulse
    static const double RESONATE_ROTATION_ENC_C		= (2.0*PI/1562500.0);	// rad/pulse
    static const double RESONATE_ROTATION_ENC_A1	= (2.0*PI/3125000.0);	// rad/pulse
    static const double RESONATE_ROTATION_ENC_A2	= (2.0*PI/3125000.0);	// rad/pulse
    static const double MAX_FORCE_X					= 36.0;					// N
    static const double MAX_FORCE_Y1				= 36.0;					// N
    static const double MAX_FORCE_Y2				= 36.0;					// N
    static const double MAX_FORCE_Z					= 36.0;					// N
    static const double MAX_TORQUE_C				= 2.0;					// N*m
    static const double MAX_TORQUE_A1				= 5.0;					// N*m
    static const double MAX_TORQUE_A2				= 5.0;					// N*m

    static const char *label[]={
        "time","ec","en-ec","en-ec(mod)","td","el(t)","el(n)","el(b)","es(y)","es(a)",
        "rpos(x)", "rvel(x)", "racc(x)", "pos(x)", "vel(x)", "acc(x)", "f(x)", "ew(x)",
        "rpos(y1)","rvel(y1)","racc(y1)","pos(y1)","vel(y1)","acc(y1)","f(y1)","ew(y1)",
        "rpos(y2)","rvel(y2)","racc(y2)","pos(y2)","vel(y2)","acc(y2)","f(y2)","ew(y2)",
        "rpos(z)", "rvel(z)", "racc(z)", "pos(z)", "vel(z)", "acc(z)", "f(z)", "ew(z)",
        "rpos(c)", "rvel(c)", "racc(c)", "pos(c)", "vel(c)", "acc(c)", "t(c)", "ew(c)",
        "rpos(a1)","rvel(a1)","racc(a1)","pos(a1)","vel(a1)","acc(a1)","t(a1)","ew(a1)",
        "rpos(a2)","rvel(a2)","racc(a2)","pos(a2)","vel(a2)","acc(a2)","t(a2)","ew(a2)","Φt","Φtd"};
    static const int NUM_DUMPDATA = sizeof(label)/sizeof(*label);			// number of loging data
    //static const unsigned int energycol[7]={17,25,33,41,49,57,65};
    static const unsigned int energycol[2]={17,25};

}













#endif // DEFINE

