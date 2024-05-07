#include "model.h"
#include "BasicWindowsAPI/application_main.h"

void RenderCart(model Cart, graphics_offscreen_buffer *Buffer, int Y, int X, unsigned int *Pixel)
{   
    int XOrigin = (Buffer->Width/2);
    int YOrigin = (Buffer->Height/2);
    int HalfCart = 50;
    int LeftSideOfCart = (int)Cart.Cart.XPos - HalfCart + XOrigin;
    int RightSideOfCart = LeftSideOfCart + (2 * HalfCart);
    if(Y < (YOrigin + 25) && Y > (YOrigin - 25))
    {
            if(X >= LeftSideOfCart && X <= RightSideOfCart)
            {
                *(uint32_t *)Pixel = 0x123456;       
            }
    }
    return;
}

void RenderPendulum(application_state *ApplicationState, graphics_offscreen_buffer *Buffer, int Y, int X, unsigned int *Pixel)
{
    int XOrigin = (Buffer->Width/2);
    int YOrigin = (Buffer->Height/2);
    double Scale = 150.0f;
    double Angle =  (- ApplicationState->CartPendulum.Pendulum.XPos + ApplicationState->CartPendulum.Cart.XPos);
    double XPosition = (Scale * (Angle)) + ApplicationState->CartPendulum.Cart.XPos;
    double YPosition = Scale * ApplicationState->CartPendulum.Pendulum.YPos;
    double Radius = 10;
    if((pow((double)X - XPosition - (double)XOrigin, 2) + pow((double)Y - YPosition - (double)YOrigin, 2)) < pow(Radius, 2))
    {
        *Pixel = 0x123456;
    }
}
void RenderRod(application_state *ApplicationState, graphics_offscreen_buffer *Buffer, int Y, int X, unsigned int *Pixel)
{
    double gradX = ApplicationState->CartPendulum.Cart.XPos - (ApplicationState->CartPendulum.Pendulum.XPos);
    double gradY = ApplicationState->CartPendulum.Cart.YPos - (ApplicationState->CartPendulum.Pendulum.YPos);
    double Angle =  (- ApplicationState->CartPendulum.Pendulum.XPos + ApplicationState->CartPendulum.Cart.XPos);
    double Gradient = - gradY / gradX;
    double Scale = 150;
    if(gradY == 0)
    {
        Gradient = 0;
    }
    if(gradX == 0)
    {
        
        return;
    }
    // double XC = (double) ApplicationState->CartPendulum.Cart.XPos + (double) X + Buffer->Width/2;
    // double XA = ((double)XC) * Gradient;
    // int XB = (int)XA;
    if((int)((X - ApplicationState->CartPendulum.Cart.XPos - Buffer->Width/2)* Gradient) + Buffer->Height/2 == (int)Y || (int)((X + 1 - ApplicationState->CartPendulum.Cart.XPos - Buffer->Width/2)* Gradient) + Buffer->Height/2 == (int)Y)
    {
        if(X  - Buffer->Width/2 < ApplicationState->CartPendulum.Cart.XPos && ApplicationState->CartPendulum.Cart.XPos > ApplicationState->CartPendulum.Pendulum.XPos)
        {
            return;
        }
        if(X  - Buffer->Width/2 > ApplicationState->CartPendulum.Cart.XPos && ApplicationState->CartPendulum.Cart.XPos < ApplicationState->CartPendulum.Pendulum.XPos)
        {
            return;
        }
        if(X - Buffer->Width/2 < (Scale * (Angle)) + ApplicationState->CartPendulum.Cart.XPos && ApplicationState->CartPendulum.Cart.XPos < ApplicationState->CartPendulum.Pendulum.XPos)
        {
            return;
        }
        if(X - Buffer->Width/2 > (Scale * (Angle)) + ApplicationState->CartPendulum.Cart.XPos && ApplicationState->CartPendulum.Cart.XPos > ApplicationState->CartPendulum.Pendulum.XPos)
        {
            return;
        }
        *(uint32_t *)Pixel = 0x123456;
    }
}
