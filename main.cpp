#include<iostream>
#include<cmath>

#include"BasicWindowsAPI/win64_main.cpp"

void MainUpdate(graphics_offscreen_buffer *Buffer, application_memory *Memory)
{
    
    application_state *ApplicationState = (application_state *)Memory->PermanentStorage;
    if(!Memory->IsInitialized)
    {
        ApplicationState->CartPendulum.Gravity = 9.8;

        ApplicationState->CartPendulum.Friction =  0;

        ApplicationState->CartPendulum.Cart.Mass = 1;
        ApplicationState->CartPendulum.Cart.XPos = 0;
        ApplicationState->CartPendulum.Cart.YPos = 0;
        ApplicationState->CartPendulum.Cart.XSpeedOfCart = 0;
        ApplicationState->CartPendulum.Cart.YSpeedOfCart = 0;
        ApplicationState->CartPendulum.Cart.XAccelerationOfCart = 0;
        ApplicationState->CartPendulum.Cart.YAccelerationOfCart = 0;
        ApplicationState->CartPendulum.Cart.XForceActingOnCart = 0;
        
        ApplicationState->CartPendulum.Pendulum.LengthOfPendulum = 1;
        ApplicationState->CartPendulum.Pendulum.AngleOfPendulum = 0;
        ApplicationState->CartPendulum.Pendulum.Mass = 1;
        ApplicationState->CartPendulum.Pendulum.XPos = ApplicationState->CartPendulum.Cart.XPos - ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * sin(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
        ApplicationState->CartPendulum.Pendulum.YPos = ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * cos(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
        ApplicationState->CartPendulum.Pendulum.XSpeedOfPendulum = 0;
        ApplicationState->CartPendulum.Pendulum.YSpeedOfPendulum = 0;
        ApplicationState->CartPendulum.Pendulum.XAccelerationOfPendulum = 0;
        ApplicationState->CartPendulum.Pendulum.YAccelerationOfPendulum = 0;

        Memory->IsInitialized = true;
    }
}