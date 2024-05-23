#pragma Once

#include "model.h"
#include <math.h>
/*
This is the State-Space Representation of my system of equations

y = [theta, theta dot, X(t), X(t) dot]
y dot = [theta dot , theta dot dot, X(t) dot, X(t) dot dot]
y dot = [theta dot, (theta * m)/M + u(t)/M, X(t) dot, theta(M+m)/M + u(t)/M]

We m be the weight of pendulum, M be the weight of the Cart and u(t) by the force applied to the cart.
*/

struct SystemStates
{
    double ThetaDot;
    double ThetaDotDot;
    double Xdot;
    double Xdotdot;
};

void RK4(model *Model)
{
    double pi = 3.14;
    double d = 0.1f;
    double b = 0.5f;
    double h;
    h = 0.02;
    double U;
    U = 0;
    SystemStates k1;
    k1.ThetaDot = Model->Pendulum.SpeedOfPendulum;
    k1.ThetaDotDot = (-Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*Model->Pendulum.SpeedOfPendulum*Model->Pendulum.SpeedOfPendulum*sinf(Model->Pendulum.AngleOfPendulum)* cosf(Model->Pendulum.AngleOfPendulum) - (Model->Cart.Mass + Model->Pendulum.Mass)*Model->Gravity*sinf(Model->Pendulum.AngleOfPendulum)+ d * Model->Cart.SpeedOfCart * cosf(Model->Pendulum.AngleOfPendulum)- (1+(Model->Cart.Mass / Model->Pendulum.Mass))*(b/Model->Pendulum.LengthOfPendulum)*Model->Pendulum.SpeedOfPendulum)
                        / (Model->Pendulum.LengthOfPendulum * Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    k1.Xdot = Model->Cart.SpeedOfCart;
    k1.Xdotdot = (Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*Model->Pendulum.SpeedOfPendulum*Model->Pendulum.SpeedOfPendulum*sinf(Model->Pendulum.AngleOfPendulum) + Model->Pendulum.Mass * Model->Gravity * sinf(Model->Pendulum.AngleOfPendulum) * cosf(Model->Pendulum.AngleOfPendulum) - d * Model->Cart.SpeedOfCart + (b/Model->Pendulum.LengthOfPendulum) * Model->Pendulum.SpeedOfPendulum * cosf(Model->Pendulum.AngleOfPendulum))
                        / (Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k2;
    double k2Pen = (h * k1.ThetaDot)/2;
    double k2Cart = ((h * k1.Xdot)/2);
    k2.ThetaDot = Model->Pendulum.SpeedOfPendulum ;
    k2.ThetaDotDot = (-Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*(Model->Pendulum.SpeedOfPendulum + k2Pen)*(Model->Pendulum.SpeedOfPendulum +k2Pen)*sinf(Model->Pendulum.AngleOfPendulum)*cosf(Model->Pendulum.AngleOfPendulum) - (Model->Cart.Mass + Model->Pendulum.Mass)*Model->Gravity*sinf(Model->Pendulum.AngleOfPendulum)+ d * Model->Cart.SpeedOfCart * cosf(Model->Pendulum.AngleOfPendulum)- (1+(Model->Cart.Mass / Model->Pendulum.Mass))*(b/Model->Pendulum.LengthOfPendulum)*(Model->Pendulum.SpeedOfPendulum+ (h * k1.ThetaDot)/2))
                        / (Model->Pendulum.LengthOfPendulum * Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
k2.Xdot = Model->Cart.SpeedOfCart;
    k2.Xdotdot = (Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*Model->Pendulum.SpeedOfPendulum*Model->Pendulum.SpeedOfPendulum*sinf(Model->Pendulum.AngleOfPendulum) + Model->Pendulum.Mass * Model->Gravity * sinf(Model->Pendulum.AngleOfPendulum) * cosf(Model->Pendulum.AngleOfPendulum) - d * (Model->Cart.SpeedOfCart + k2Cart) + (b/Model->Pendulum.LengthOfPendulum) * Model->Pendulum.SpeedOfPendulum * cosf(Model->Pendulum.AngleOfPendulum))
                        / (Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k3;
    double k3Pen = (h * k2.ThetaDot)/2;
    double k3Cart = (h * k2.Xdot)/2;
    k3.ThetaDot = Model->Pendulum.SpeedOfPendulum ;
    k3.ThetaDotDot = (-Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*(Model->Pendulum.SpeedOfPendulum + k3Pen)*(Model->Pendulum.SpeedOfPendulum +k3Pen)*sinf(Model->Pendulum.AngleOfPendulum)*cosf(Model->Pendulum.AngleOfPendulum) - (Model->Cart.Mass + Model->Pendulum.Mass)*Model->Gravity*sinf(Model->Pendulum.AngleOfPendulum)+ d * Model->Cart.SpeedOfCart * cosf(Model->Pendulum.AngleOfPendulum)- (1+(Model->Cart.Mass / Model->Pendulum.Mass))*(b/Model->Pendulum.LengthOfPendulum)*(Model->Pendulum.SpeedOfPendulum+ k3Pen))
                        / (Model->Pendulum.LengthOfPendulum * Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k3.Xdot = Model->Cart.SpeedOfCart;
    k3.Xdotdot = (Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*Model->Pendulum.SpeedOfPendulum*Model->Pendulum.SpeedOfPendulum*sinf(Model->Pendulum.AngleOfPendulum) + Model->Pendulum.Mass * Model->Gravity * sinf(Model->Pendulum.AngleOfPendulum) * cosf(Model->Pendulum.AngleOfPendulum) - d * (Model->Cart.SpeedOfCart + k3Cart)+ (b/Model->Pendulum.LengthOfPendulum) * Model->Pendulum.SpeedOfPendulum * cosf(Model->Pendulum.AngleOfPendulum))
                        / (Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k4 = k3;
    double k4Pen = (h * k3.ThetaDot);
    double k4Cart = (h * k3.Xdot);
    k4.ThetaDot = Model->Pendulum.SpeedOfPendulum;
    k3.ThetaDotDot = (-Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*(Model->Pendulum.SpeedOfPendulum + k4Pen)*(Model->Pendulum.SpeedOfPendulum +k4Pen)*sinf(Model->Pendulum.AngleOfPendulum)*cosf(Model->Pendulum.AngleOfPendulum) - (Model->Cart.Mass + Model->Pendulum.Mass)*Model->Gravity*sinf(Model->Pendulum.AngleOfPendulum)+ d * Model->Cart.SpeedOfCart * cosf(Model->Pendulum.AngleOfPendulum)- (1+(Model->Cart.Mass / Model->Pendulum.Mass))*(b/Model->Pendulum.LengthOfPendulum)*(Model->Pendulum.SpeedOfPendulum+ k4Pen))
                        / (Model->Pendulum.LengthOfPendulum * Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k4.Xdot = Model->Cart.SpeedOfCart;
    k4.Xdotdot = (Model->Pendulum.Mass*Model->Pendulum.LengthOfPendulum*Model->Pendulum.SpeedOfPendulum*Model->Pendulum.SpeedOfPendulum*sinf(Model->Pendulum.AngleOfPendulum) + Model->Pendulum.Mass * Model->Gravity * sinf(Model->Pendulum.AngleOfPendulum) * cosf(Model->Pendulum.AngleOfPendulum) - d * (Model->Cart.SpeedOfCart + k4Cart) + (b/Model->Pendulum.LengthOfPendulum) * Model->Pendulum.SpeedOfPendulum * cosf(Model->Pendulum.AngleOfPendulum))
                        / (Model->Cart.Mass + Model->Pendulum.Mass * (sinf(Model->Pendulum.AngleOfPendulum)*sinf(Model->Pendulum.AngleOfPendulum)));//((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    Model->Pendulum.AngleOfPendulum = Model->Pendulum.AngleOfPendulum + (h/6)*(k1.ThetaDot + 2 * k2.ThetaDot + 2*k3.ThetaDot + k4.ThetaDot);
    Model->Pendulum.SpeedOfPendulum = Model->Pendulum.SpeedOfPendulum + (h/6)*(k1.ThetaDotDot + 2 * k2.ThetaDotDot + 2*k3.ThetaDotDot + k4.ThetaDotDot);
    Model->Cart.XPos = Model->Pendulum.XPos + (h/6)*(k1.Xdot + 2 * k2.Xdot + 2*k3.Xdot + k4.Xdot);
    Model->Cart.SpeedOfCart = Model->Pendulum.SpeedOfPendulum + (h/6)*(k1.Xdotdot + 2 * k2.Xdotdot + 2*k3.Xdotdot + k4.Xdotdot);


}
