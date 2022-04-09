#region

// System Imports
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

// Discord Imports
using Discord;
using Discord.Commands;
using Discord.WebSocket;
//using PacketBot.Modules;

//Other Imports
using NekosSharp;
#endregion

namespace Bot
{
    class Program
    {
        static void Main(string[] args) => new Program().InitBot().GetAwaiter().GetResult();

        #region Variables
        ulong founderID = 295709920655966210;
        ulong packetID = 933153535242141767;
        ulong pandaID = 698569113664225330;
        ulong deqID = 453272260556619777;
        string prefix = BotConfig.prefix;
        static string packetLogo = "https://i.imgur.com/BmqqcV8.png";
        static string footerText = "Made by Packet Dev Team";
        public string cmdLog = "Command Ran: "; //Reduces size in the long run and bc console will be kooler
        public static NekosSharp.NekoClient NekoClient = new NekoClient("KysNeko");
        #endregion

        #region Functions
        void doAutoClear()
        {
            while (true)
            {
                Console.Clear();
                Thread.Sleep(900 * 1000); //15mins
            }
        }

        void consoleLog(string textToPrint)
        {
            Console.WriteLine(cmdLog + " " + textToPrint);
        }

        void nap(int seconds) //prevent spam
        {
            Thread.Sleep(seconds * 1000);//since sleep is using ms, multiply by 1000 so you get a second
        }
        #endregion

        public async Task InitBot()
        {
            BotConfig._client = new DiscordSocketClient();

            BotConfig._client.MessageReceived += HandleCommandAsync;

            await BotConfig._client.LoginAsync(TokenType.Bot, BotConfig.token);
            await BotConfig._client.StartAsync();

            Thread autoclsThread = new Thread(new ThreadStart(doAutoClear));
            autoclsThread.Start();

            Console.Title = "Packet Bot Running...";
            Console.WriteLine("Initiated");

            await Task.Delay(-1); // Don't place things under this otherwise it won't run
        }

        private async Task HandleCommandAsync(SocketMessage arg)
        {
            try
            {
                var msg = arg as SocketUserMessage;
                string faq = "<#933162233251385346>";

                #region Checks and Functions
                bool isStaff()
                {
                    if (msg.Author.Id == founderID || msg.Author.Id == packetID || msg.Author.Id == pandaID || msg.Author.Id == deqID)
                    {
                        return true;
                    } else
                    {
                        return false;
                    }
                }
                #endregion

                #region Triggers
                if (msg is null || msg.Author.IsBot) return;

                if (msg.Content == "ct" && msg.Author.CreatedAt == DateTime.Now.AddDays(-5))
                {
                    Console.WriteLine("\n Warning:"+msg.Author.CreatedAt);
                } else if (msg.Content == "ct")
                {
                    Console.WriteLine("\neee (Safe)");
                }

                if (msg.Content.ToLower().Contains("how"))
                {
                    if (msg.Author.Id == founderID) return;
                    await msg.ReplyAsync(faq);
                    consoleLog(msg.Author.Username + " --> how");
                    nap(2);
                    return;
                }

                if (msg.Content.ToLower().Contains("help") && !isStaff())
                {
                    if (msg.Author.Id == founderID) return;
                    await msg.ReplyAsync(faq);
                    consoleLog(msg.Author.Username + " --> help");
                    nap(2);
                    return;
                }

                if (msg.Content.ToLower().Contains("crash") && !isStaff())
                {
                    if (msg.Author.Id == founderID) return;
                    await msg.ReplyAsync("skill issue");
                    consoleLog(msg.Author.Username + " --> crash");
                    nap(2);
                    return;
                }

                //Useless but funni stuff below
                if (msg.Content.ToLower().Contains("dead chat") || msg.Content.ToLower().Contains("dead-chat"))
                {
                    await msg.ReplyAsync("then make it alive");
                    consoleLog(msg.Author.Username + " --> dead chat");
                    nap(2);
                    return;
                }

                if (msg.Content.ToLower().Contains("uwu owo"))
                {
                    if (msg.Author.Id == founderID) return;
                    await msg.ReplyAsync("no ur gay");
                    consoleLog(msg.Author.Username + " --> uwu owo");
                    nap(2);
                    return;
                }

                if (msg.Content.ToLower().Contains("cock and balls"))
                {
                    await msg.ReplyAsync("my cock and balls are rotating");
                    consoleLog(msg.Author.Username + " --> cock and balls");
                    nap(2);
                    return;
                }

                #endregion

                #region Staff
                if (msg.Content == "e" && isStaff())
                {
                    await msg.ReplyAsync("e");
                    consoleLog(msg.Author.Username + " --> e");
                    nap(2);
                    return;
                }
                #endregion

                #region Commands

                if (msg.Content == prefix + "test" && isStaff())
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    var eb = new EmbedBuilder();
                        eb.WithDescription("description test - "+msg.Channel.GetCachedMessages(1).ToList().ToString());
                        eb.WithFooter(footerText, packetLogo);
                        eb.WithImageUrl("https://i.imgur.com/BmqqcV8.png");
                        await msg.Channel.SendMessageAsync("", false, eb.Build());
                        consoleLog(msg.Author.Username + " --> command-test");
                        nap(2);
                        return;
                }

                #region HelpLists
                if (msg.Content == prefix + "cmds")
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    consoleLog(msg.Author.Username + " --> help cmds");
                    var ebHelplist = new EmbedBuilder();
                    ebHelplist.WithTitle("Commands List");
                    ebHelplist.WithFooter(footerText, packetLogo);
                    ebHelplist.AddField(prefix + "cmds", "*Displays this list*");
                    ebHelplist.AddField(prefix + "misc", "*Displays miscellaneous commands*");
                    ebHelplist.AddField(prefix + "staff", "*Displays staff commands*");
                    ebHelplist.AddField(prefix + "nsfw", "*Displays NSFW commands*");
                    await msg.Channel.SendMessageAsync("", false, ebHelplist.Build());
                    nap(2);
                    return;
                }

                if (msg.Content == prefix + "misc")
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    consoleLog(msg.Author.Username + " --> misc cmds");
                    var ebMisclist = new EmbedBuilder();
                    ebMisclist.WithTitle("Miscellaneous Commands");
                    ebMisclist.WithFooter(footerText, packetLogo);
                    ebMisclist.AddField(prefix + "test", "*Command used for testing*");
                    ebMisclist.AddField(prefix + "neko", "*Displays a random neko*");
                    ebMisclist.AddField(prefix + "fox", "*Displays a random fox (aka kitsune)*");
                    await msg.Channel.SendMessageAsync("", false, ebMisclist.Build());
                    nap(2);
                    return;
                }

                if (msg.Content == prefix + "staff" && isStaff())
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    consoleLog(msg.Author.Username + " --> staff cmds");
                    var ebStafflist = new EmbedBuilder();
                    ebStafflist.WithTitle("Staff Commands");
                    ebStafflist.WithFooter(footerText, packetLogo);
                    ebStafflist.AddField(prefix + "kick <userID>", "*Kick user by id*");
                    ebStafflist.AddField(prefix + "cd <userID>", "*Get mentioned user's creation date*");
                    await msg.Channel.SendMessageAsync("", false, ebStafflist.Build());
                    nap(1);
                    return;
                } else if (msg.Content == prefix + "staff" && !isStaff())
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    consoleLog(msg.Author.Username + " --> staff cmds [INVALID]");
                    await msg.Channel.SendMessageAsync("You must be a staff to use this command.");
                    nap(2);
                    return;
                }

                if (msg.Content == prefix + "nsfw")
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    consoleLog(msg.Author.Username + " --> nsfw cmds");
                    var ebNsfwlist = new EmbedBuilder();
                    ebNsfwlist.WithTitle("NSFW Commands");
                    ebNsfwlist.WithFooter(footerText, packetLogo);
                    ebNsfwlist.AddField(prefix + "hentai", "*Random hentai*");
                    ebNsfwlist.AddField(prefix + "hentaigif", "*Random hentai gif*");
                    await msg.Channel.SendMessageAsync("", false, ebNsfwlist.Build());
                    nap(2);
                    return;
                }
                #endregion

                if (msg.Content == prefix + "neko")
                {
                    if (msg.Author.Id == packetID) return;
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    Request Req = await NekoClient.Image.Neko();
                    try
                    {
                        var eb = new EmbedBuilder();
                        eb.WithDescription("Random Neko!");
                        eb.WithFooter(footerText, packetLogo);
                        if (Req.Success)
                            eb.WithImageUrl(Req.ImageUrl);
                        else
                            eb.WithImageUrl(packetLogo);
                        await msg.Channel.SendMessageAsync("", false, eb.Build());
                        consoleLog(msg.Author.Username + " --> neko");
                        nap(2);
                        return;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("Fucky wucky " + e + "  |  " + Req.Error);
                    }
                }

                if (msg.Content == prefix + "fox")
                {
                    await msg.Channel.DeleteMessageAsync(msg.Id);
                    Request Req = await NekoClient.Image.Fox();
                    try
                    {
                        var eb = new EmbedBuilder();
                        eb.WithDescription("Random Fox!");
                        eb.WithFooter(footerText, packetLogo);
                        if (Req.Success)
                            eb.WithImageUrl(Req.ImageUrl);
                        else
                            eb.WithImageUrl(packetLogo);
                        await msg.Channel.SendMessageAsync("", false, eb.Build());
                        consoleLog(msg.Author.Username + " --> fox");
                        nap(2);
                        return;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("Fucky wucky " + e + "  |  " + Req.Error);
                    }
                }


                if (msg.Content == prefix + "cd")
                {
                        await msg.Channel.DeleteMessageAsync(msg.Id);
                        var eb = new EmbedBuilder();
                        eb.WithDescription("CD HERE");
                        eb.WithFooter(footerText, packetLogo);
                        await msg.Channel.SendMessageAsync("", false, eb.Build());
                        consoleLog(msg.Author.Username + " --> creation date");
                        nap(1);
                        return;
                }
                #endregion

            }
            catch
            {
            }
        }
    }
}