using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DummyClient
{
    static class Program
    {
        public static DummyClient mainForm_ = null;
        public static ProgramState programState_ = null;
        /// <summary>
        /// 해당 응용 프로그램의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // 메인, 상태 폼 static -> 하나만 존재 해야하는 클래스(여기선 싱글턴 처럼 사용됨)
            mainForm_ = new DummyClient();
            programState_ = new ProgramState();
            Application.Run(mainForm_);
            Application.Exit();
        }
    }
}
