#include "model.h"
#include "BasicWindowsAPI/application_main.h"

void RenderCart(model Cart, graphics_offscreen_buffer *Buffer, int Y, int X, unsigned int *Pixel)
{   
    int XOrigin = (Buffer->Width/2);
    int YOrigin = (Buffer->Height/2);
    int HalfCart = 50;
    int LeftSideOfCart = Cart.Cart.XPos - HalfCart + XOrigin;
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

void RenderPendulum(model Pendulum, graphics_offscreen_buffer *Buffer, int Y, int X, unsigned int *Pixel)
{
    int XOrigin = (Buffer->Width/2);
    int YOrigin = (Buffer->Height/2);
    int CenterXAxis = X - XOrigin;
    int CenterYAxis = Y - YOrigin;
    double MoveXDirection = (double)CenterXAxis + (double)Pendulum.Pendulum.XPos;
    double MoveYDirection = (double)CenterYAxis + (double)Pendulum.Pendulum.YPos;
    double ScaledX = MoveXDirection; 
    double ScaledY = MoveYDirection;
    if(Pendulum.Pendulum.XPos > 0)
    {
        ScaledX = MoveXDirection + 150;
    }
    else if (Pendulum.Pendulum.XPos < 0)
    {
        ScaledX = MoveYDirection - (150);
    }
    if(Pendulum.Pendulum.YPos > 0)
    {
        ScaledY = MoveYDirection + 150;
    }
    else if (Pendulum.Pendulum.YPos < 0)
    {
        ScaledY = MoveYDirection - (150);
    }
    float Radius = 10;
    if ((pow((double)(ScaledX), 2) + pow((double)(ScaledY), 2)) < pow(Radius, 2))
    {
        *(uint32_t *)Pixel = 0x123456;       
    }
}











    