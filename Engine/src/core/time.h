#ifndef TIME_H
#define TIME_H

namespace overflow
{
    class Time
    {
    public:
	    static void Update(double delta);
	    static void Update_Current(double time);
	    
	    static float DeltaF() { return (float)s_Delta; }
	    static double Delta() { return s_Delta; }
	    
	    static float UDeltaF() { return (float)s_U_Delta; }
	    static double UDelta() { return s_U_Delta; }
	    
	    static double GetTime() { return s_Time; }
	    static double GetUTime() { return s_U_Time; }
	    
	    static float TimeScale() { return (float)s_Scale; }
	    static void SetTimeScale(float scale)
	    {
		    if(scale < 0) scale = 0;
		    s_Scale = (double)scale;
	    }
    
    private:
	    static double s_Scale;
	    static double s_Time;
	    static double s_Delta;
	    
	    static double s_U_Time;
	    static double s_U_Delta;
    };
}

#endif //TIME_H
