using System;
using System.Windows.Forms;
using GTA;

public class Fixes : Script
{
    Weapon lastWeapon = Weapon.Unarmed;

    public Fixes()
    {
        // Evento acionado ao carregar o script
        Tick += OnTick;
        KeyDown += OnKeyDown;

        Game.DisplayText("Fixes: Running", 3000);
        Game.Console.Print("Player Model: " + Player.Model);
    }

    private void OnTick(object sender, EventArgs e)
    {
        // Ped player = Player.Character;
        // // extern boolean IS_MOBILE_PHONE_CALL_ONGOING(void);
        // AnimationFlags animflags = AnimationFlags.Unknown12 | AnimationFlags.Unknown11 | AnimationFlags.Unknown09;

        // if (GTA.Native.Function.Call<bool>("HAVE_ANIMS_LOADED", "cellphone_talk"))
        // //if (Player.Character.Animation.Play(anims, "cellphone", 8.0F, animflags))
        // {
        //     //if (Player.Character.Weapons.CurrentType != Weapon.Unarmed)
        //     //{
        //         Player.Character.Weapons.Unarmed.Select();
        //     //}
        // }
    }

    private void OnKeyDown(object sender, GTA.KeyEventArgs e)
    {

        if (e.Key == Keys.N)
        {
           // BLOCK_PED_WEAPON_SWITCHING(Ped ped, boolean value);
           Game.DisplayText("Player can't switch guns: active", 3000);
           Ped ped = Player.Character;
           GTA.Native.Function.Call("BLOCK_PED_WEAPON_SWITCHING", ped, true);
        }
    }

}
