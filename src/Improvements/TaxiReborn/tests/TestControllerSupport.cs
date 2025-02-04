/*
   ControllerSupport By Caio Madeira. 2025.
   https://github.com/caiomadeira/VCNG-Improvements
   Is a Project and part of ViceCity Next Gen Improvements
   Give the credits.
*/

using System;
using System.Windows.Forms;
using GTA;

public class TestControllerSupport : Script {
    public TestControllerSupport() 
    {
        this.KeyDown += OnKeyDown;
        this.Tick += OnTick;
        Game.DisplayText("Controller Support\nBy caiomadeira\n\ngithub.com/caiomadeira", 5000);
    }
    private void OnTick(object sender, EventArgs e)
    {   
        /*
            GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 0, 4): 
                - 0: the group (keyboard);
                - 4: (On Foot) Attack
        */

        if (((GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 0, 4)) && (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))))
        {
            GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "ATTACK BUTTON PRESSED", 2000, true);
        }

        if (((GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 2, 9)) && (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))))
        {
            GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "Left arrow PRESSED", 2000, true);
        }

        // 23	On Foot	Action
        if (((GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 2, 23)) && (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))))
        {
            GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "LB BUTTON PRESSED", 2000, true);
        }
        // 2	On Foot	Jump;  (IN VEHICLE) 41
        if (((GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 2, 2)) && (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))))
        {
            GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "X BUTTON PRESSED", 2000, true);
        }
        // 1	On Foot	Sprint; (IN VEHICLE) 42
        if (((GTA.Native.Function.Call<bool>("IS_CONTROL_PRESSED", 2, 1)) && (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))))
        {
            GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "A BUTTON PRESSED", 2000, true);
        }

        if (GTA.Native.Function.Call<bool>("IS_USING_CONTROLLER"))
        {
            // GTA.Native.Function.Call("PRINT_STRING_WITH_LITERAL_STRING_NOW", "STRING", "Sim, usando o controle.", 2000, true);
            Game.DisplayText("Usando o controle.");
        } else 
        {
            Game.DisplayText("Usando o teclado.");
        }

    }

    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {
        
    }
}