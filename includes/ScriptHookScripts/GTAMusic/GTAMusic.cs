using System;
using System.Threading.Tasks;
using System.Windows.Forms;
using GTA;
using SpotifyAPI.Web;

namespace GTAMusic
{
    public class GTAMusic : Script
    {
        private static SpotifyClient spotify;
        private static FullTrack track;
        public GTAMusic()
        {
            Tick += OnTick;
            KeyDown += OnKeyDown; // Descomente essa linha se for usar o OnKeyDown
        }

        static async Task InitializeSpotify()
        {
            var config = SpotifyClientConfig.CreateDefault();

            var request = new ClientCredentialsRequest("f9ff0fca79aa4af6b20e529d7eb880cc", "731c4bc90a6040dda0453397aaf1c61b");
            var response = await new OAuthClient(config).RequestToken(request);

            var spotify = new SpotifyClient(config.WithToken(response.AccessToken));
            track = await spotify.Tracks.Get("1s6ux0lNiTziSrd7iUAADH");
            Console.WriteLine(track.Name);
            Game.DisplayText("Spotify conectado!", 3000);

        }

        private async void OnTick(object sender, EventArgs e)
        {
            if (spotify != null) { Game.DisplayText("Spotify conectado!", 3000); }
        }

        private void OnKeyDown(object sender, GTA.KeyEventArgs e)
        {
            // Exemplo de chave para pausar/reiniciar música
            if (e.Key == Keys.H)
            {
                InitializeSpotify();
                if (track != null)
                {
                    Game.DisplayText(track.Name, 3000);
                }
            }
        }
    }
}
