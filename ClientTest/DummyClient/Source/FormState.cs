using System.Threading;
using System.Windows.Forms;

namespace DummyClient
{
    internal abstract class FormState
    {
        protected Form form_;
        protected Network network_;

        public abstract void open();
        public abstract bool connect(string ip, uint port);

        protected void setForm()
        {
            form_.TopLevel = false;
            form_.Dock = System.Windows.Forms.DockStyle.Fill;
            Program.mainForm_.Invoke(new MethodInvoker(delegate()
            {
                form_.Parent = Program.mainForm_.mainPanel_;
                form_.Show();
            }));
        }

        public void close()
        {
            Program.mainForm_.removePanelForm(ref form_);
            if (network_ != null)
                network_.disConnect();

            Thread.Sleep(1);
            form_.Hide();
        }

        public bool connectToServer(string ip, uint port)
        {
            if (network_ == null)
                network_ = new Network();

            return network_.connect(ip, port);
        }

        public void sendPacket(ref PacketInterface packet)
        {
            network_.sendPacket(packet);
        }
    }

    internal class LoginFormState : FormState
    {
        public override void open()
        {
            form_ = new LoginForm();
            setForm();
        }

        public override bool connect(string ip, uint port)
        {
            if (!base.connectToServer(ip, port))
            {
                var result = MessageBox.Show("로그인 서버 연결에 실패. 다시 연결 시도 해볼까요?", "error", MessageBoxButtons.RetryCancel);
                if (result != DialogResult.Retry)
                {
                    form_.Close();
                    //Application.Exit();
                }

                return false;
            }
            network_.setPacketProcess(new LoginPacketProcess());

            return true;
        }
    }

    internal class LobbyFormState : FormState
    {
        public override void open()
        {
            form_ = new LobbyForm();
            setForm();
        }

        public override bool connect(string ip, uint port)
        {
            if (!base.connectToServer(ip, port))
            {
                MessageBox.Show("채팅 서버 연결에 실패 했습니다..", "error", MessageBoxButtons.OK);
                Program.programState_.setState(PROGRAM_STATE.LOGIN);
                return false;
            }

            network_.setPacketProcess(new LobbyPacketProcess());
            return true;
        }
    }
}