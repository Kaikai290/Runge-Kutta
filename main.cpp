#include<iostream>
#include<cmath>

#include "BasicWindowsAPI/win64_main.cpp"
#include "render.cpp"
#include "model.h"
#include "rugne-kutta.cpp"

void MainUpdate(application_state *ApplicationState)
{
    
    if(!ApplicationState->IsInitialized)
    {
        //TODO: Add more memory value if common shared values between functions
        ApplicationState->CartPendulum.Gravity = 9.8f;

        ApplicationState->CartPendulum.Friction =  0.0f;

        ApplicationState->CartPendulum.Cart.Mass = 1;
        ApplicationState->CartPendulum.Cart.XPos = 0;
        ApplicationState->CartPendulum.Cart.YPos = 0;
        ApplicationState->CartPendulum.Cart.SpeedOfCart = 0;
        ApplicationState->CartPendulum.Cart.AccelerationOfCart = 0;
        ApplicationState->CartPendulum.Cart.XForceActingOnCart = 0;
        
        ApplicationState->CartPendulum.Pendulum.LengthOfPendulum = 1;
        ApplicationState->CartPendulum.Pendulum.AngleOfPendulum = 3.1f;
        ApplicationState->CartPendulum.Pendulum.Mass = 1;
        ApplicationState->CartPendulum.Pendulum.XPos = ApplicationState->CartPendulum.Cart.XPos - ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * sin(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
        ApplicationState->CartPendulum.Pendulum.YPos = ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * cos(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
        ApplicationState->CartPendulum.Pendulum.SpeedOfPendulum = 0;
        ApplicationState->CartPendulum.Pendulum.AccelerationOfPendulum = 0;

        ApplicationState->IsInitialized = true;
    }
    //ApplicationState->CartPendulum.Pendulum.AngleOfPendulum += 0.01f;
    //ApplicationState->CartPendulum.Cart.XPos = 150*sin(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
    RK4(&ApplicationState->CartPendulum);
    ApplicationState->CartPendulum.Pendulum.XPos =  ApplicationState->CartPendulum.Cart.XPos - ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * sin(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
    ApplicationState->CartPendulum.Pendulum.YPos = - ApplicationState->CartPendulum.Pendulum.LengthOfPendulum * cos(ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
    printf_s("%.02f", ApplicationState->CartPendulum.Pendulum.AngleOfPendulum);
}

void RenderReset(graphics_offscreen_buffer *Buffer)
{
    uint8_t *Row = (uint8_t *)Buffer->Memory;
    for(int Y = 0; Y < Buffer->Height; ++Y)
    {
        uint32_t *Pixel = (uint32_t *)Row;
        for (int X = 0; X < Buffer->Width; ++X)
        {
            *Pixel++ = 0x000000;
        }
        Row += Buffer->Pitch;
  }
}

void Render(graphics_offscreen_buffer *Buffer, application_state *ApplicationState)
{
    RenderReset(Buffer);
    uint8_t *Row = (uint8_t *)Buffer->Memory;
    for(int Y = 0; Y < Buffer->Height; ++Y)
    {
        uint32_t *Pixel = (uint32_t *)Row;
        for(int X = 0; X < Buffer->Width; ++X)
        {
            //TODO: The cart and pendulum will never occupy the same space to can skip the pendulum cal if render cart changes the pixel color
            RenderCart(ApplicationState->CartPendulum, Buffer, Y, X, Pixel);
            RenderPendulum(ApplicationState, Buffer, Y, X, Pixel);
            RenderRod(ApplicationState, Buffer, Y, X, Pixel);
            Pixel++;
        }
        Row += Buffer->Pitch;
    }

    return;
}