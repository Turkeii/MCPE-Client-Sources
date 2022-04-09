using System;
using System.Reflection;
using System.Windows.Forms;

namespace PacketClient
{
    public static class Extensions
    {
        public static T Clone<T>(this T control) where T : Control
        {
            var a = typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance);
            var b = Activator.CreateInstance<T>();

            foreach (PropertyInfo c in a)
                if (c.CanWrite)
                    if (c.Name != "WindowTarget")
                        c.SetValue(b, c.GetValue(control, null), null);

            return b;
        }
        /*public static void ChangeSub<T>(this T control, string datatag, string value) where T : Control
        {
            foreach (Control bdt in control.Controls)
            {
                if (bdt.Tag.ToString() == datatag)
                    bdt.Text = value;
            }
        }*/
    }
}
