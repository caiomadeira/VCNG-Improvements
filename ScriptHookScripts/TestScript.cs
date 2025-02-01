using System;
using System.Windows.Forms;
using GTA;

public class TestScript : Script
{
    private uint clothIndex = 0;
    private bool incrementing = true;
    public TestScript()
    {
        // Evento acionado ao carregar o script
        Tick += OnTick;
        KeyDown += OnKeyDown;

        Game.DisplayText("TestScript: Running", 3000);
        Game.Console.Print("Player Model: " + Player.Model);
    }

    private void OnTick(object sender, EventArgs e)
    {
        //Game.DisplayText("RUNNING", 300);
        // 

    }

    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {
        // if (e.Key == Keys.M)
        // {
        //     Game.DisplayText("Change model", 3000);
        //     ChangeModel("IG_LILJACOBW");
        // }
        // if (e.Key == Keys.H)
        // {
        //     Game.DisplayText("Golf Clothes", 3000);
        //     Ped ped = Player.Character;
        //     // SET_CHAR_COMPONENT_VARIATION(Ped ped, uint component, uint modelVariation, uint textureVariation);
        //     /*
        //     Golf Clothes:
        //         uint modelVariation: 1
        //         uint modelVariation: 3
        //         uint textureVariation: 0
        //     */
        //     GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, 3, 0);
        //     //GTA.Native.Function.Call("SET_CHAR_COORDINATES", ped, 759.676, 737.762, 6.342);
        //     //GTA.Native.Function.Call("SET_CHAR_HEADING", ped, 125.0);
        // }

        // if (e.Key == Keys.M)
        // {
        //     Game.DisplayText("TOMMY PADRAO CLOTH", 3000);
        //     Ped ped = Player.Character;
        //     GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, 0, 0);
        // }

        // if (e.Key == Keys.N)
        // {
        //     Game.DisplayText("Terno Roxo", 3000);
        //     Ped ped = Player.Character;
        //     GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, 1, 0);
        // }

        if (e.Key == Keys.N)
        {
           // BLOCK_PED_WEAPON_SWITCHING(Ped ped, boolean value);
           Game.DisplayText("Player can't switch guns: active", 3000);
           Ped ped = Player.Character;
           GTA.Native.Function.Call("BLOCK_PED_WEAPON_SWITCHING", ped, true);
        }

        if (e.Key == Keys.L)
        {
            Game.DisplayText("Worker cloth", 3000);
            Ped ped = Player.Character;
            GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, 2, 0);
        }

        // if (e.Key == Keys.M)
        // {
        //     if (incrementing)
        //     {
        //         clothIndex++;
        //         if (clothIndex == 4)
        //             incrementing = false;
        //     } else {
        //         clothIndex--;
        //         if (clothIndex == 0)
        //             incrementing = true;
        //     }

        //     ChangeClothes(clothIndex);
        // }
    }

    // private void ChangeClothes(uint clothIndex)
    // {
    //     string clothName = "";
    //     switch(clothIndex)
    //     {
    //         case 0: clothName = "Tommy Padrao Cloth"; break;
    //         case 1: clothName = "Purple Suit Cloth"; break;
    //         case 2: clothName = "Worker Cloth"; break;
    //         case 3: clothName = "Golf Cloth"; break;
    //         case 4: clothName = "Unknown Cloth"; break;
    //     }

    //     Game.Console.Print("Player Model: " + Player.Model);
    //     Game.DisplayText(clothName, 3000);
    //     Ped ped = Player.Character;

    //     string currentModel = Player.Model.ToString();
    //     Player.Model = "PLAYER";
    //     Player.Model = currentModel;

    //     GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, clothIndex, 0);
    //     GTA.Native.Function.Call("MARK_MODEL_AS_NO_LONGER_NEEDED", ped.Model);
    //     Game.Console.Print("Applied variation");
    // }
    private void ChangeModel(string modelName)
    {
        Player.Model = modelName;

        Game.DisplayText("Modelo alterado para: {modelName}", 3000);
        Game.Console.Print("Player Model: " + Player.Model);

    }

}
