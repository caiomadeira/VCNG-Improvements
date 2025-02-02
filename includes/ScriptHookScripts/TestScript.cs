using System;
using System.Windows.Forms;
using GTA;

public class TestScript : Script
{
    private uint clothIndex = 0;
    private bool incrementing = true;
    public TestScript()
    {
        Interval = 250;
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
           
        }

        if (e.Key == Keys.L)
        {
            Game.DisplayText("Worker cloth", 3000);
            Ped ped = Player.Character;
            GTA.Native.Function.Call("SET_CHAR_COMPONENT_VARIATION", ped, 1, 2, 0);
        }
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

// Feature de fazer um refém
public class HostageTask : Script {

    TaskSequence FleeTask;

    public HostageTask() {
        this.KeyDown += OnKeyDown;
        this.Tick += OnTick;
    }

    private void OnTick(object sender, EventArgs e)
    {
        //Game.DisplayText("RUNNING", 300);
        // 

    }

    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {
        if (e.Key == Keys.K)
        {
            Ped targetPed = Player.GetTargetedPed();

            if (targetPed != null)
            {
                Game.DisplayText("Refém detectado!", 3000);
                Vector3 playerPos = Player.Character.Position;
                float heading = Player.Character.Heading * (float)(Math.PI / 180.0); // Converte graus para radianos
                Vector3 hostagePos = playerPos + new Vector3((float)Math.Cos(heading), (float)Math.Sin(heading), 0.0f) * 1.0f;

                targetPed.Position = hostagePos;
                targetPed.Heading = Player.Character.Heading + 100.0f;
                Game.DisplayText("Executando a task", 3000);
                // FleeTask = new TaskSequence();
                AnimationFlags animflags = AnimationFlags.Unknown12 | AnimationFlags.Unknown11 | AnimationFlags.Unknown09;
                // //FleeTask.AddTask.PlayAnimation(new AnimationSet("missray6"), "drop_knees", 8.0f);
                Game.DisplayText("missgerry4: hostage_taker", 3000);
                // FleeTask.AddTask.PlayAnimation(new AnimationSet("missgerry4"), "hostage_taker", 8.0f, animflags);
                Player.Character.Task.PlayAnimation(new AnimationSet("missgerry4"), "hostage_taker", 8.0f, animflags);
                // Player.Character.Task.ClearAll();
                //Player.Character.Task.PerformSequence(FleeTask);
                // FleeTask.Dispose();
                Game.DisplayText("Animação ativada!", 3000);
            }
        }
    }

}