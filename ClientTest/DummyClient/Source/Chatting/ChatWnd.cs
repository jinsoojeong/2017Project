using System;
using System.Windows.Forms;

// 채팅창의 경우 richTextBox를 통해서 메시지를 출력 용도로 사용하고 있다.
// 채팅이 진행되면 될 수록 밑으로 추가 되므로 이를 자동으로 보정하는 기능이 필요
namespace DummyClient
{
    internal class ChatWnd
    {
        private enum TextView
        {
            LINE_MAX = 5000,
        }

        //--------------------------------------------//
        private RichTextBox outputView_;

        public ChatWnd(RichTextBox richTextBox)
        {
            this.outputView_ = richTextBox;
        }

        // 5000 라인 이상 쌓이면 제거
        private void chattingMessageResize()
        {
            String str = outputView_.Text;
            int textLine = 0;

            while (true) {
                int idx = str.IndexOf(Environment.NewLine);
                if (idx < 0) {
                    break;
                }
                str = str.Substring(idx + Environment.NewLine.Length);
                ++textLine;
            }

            if (textLine > (int)TextView.LINE_MAX) {
                String originalStr = outputView_.Text;

                int idx = originalStr.IndexOf(Environment.NewLine);
                originalStr = originalStr.Substring(idx + Environment.NewLine.Length);

                outputView_.Text = originalStr;
            }
        }

        public void textChanged(object sender, EventArgs e)
        {
            chattingMessageResize();

            String str = outputView_.Text;
            int len = str.LastIndexOf('\n');

            if (len < 0)
                return;
            
            outputView_.SelectionStart = len;
            outputView_.ScrollToCaret();
        }

        public void pushText(string text)
        {
            if (outputView_ == null) {
                return;
            }
            outputView_.AppendText(text + Environment.NewLine);
            outputView_.ScrollToCaret();
        }
    }
}