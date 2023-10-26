#include "time.h"

namespace overflow
{
	double Time::s_Scale = 1.0;
	double Time::s_Time = 0.0;
	double Time::s_Delta = 0.0;
	
	double Time::s_U_Time = 0.0;
	double Time::s_U_Delta = 0.0;
	
	void Time::Update(double delta)
	{
		s_U_Delta = delta;
		s_Delta = delta * s_Scale;
		s_U_Time += delta;
		s_Time += s_Delta;
	}
	
	void Time::Update_Current(double time)
	{
		double delta = time - s_U_Time;
		Update(delta);
	}
}