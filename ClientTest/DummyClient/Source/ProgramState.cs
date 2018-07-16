// 각 전담 폼을 관리하는 클래스,
// 폼에서 특정 내용이 처리될 때 다른 폼으로 전환하기 위한 내용을 담고 있다.

namespace DummyClient
{
    internal enum PROGRAM_STATE
    {
        LOGIN,
        LOBBY,
        GAME,
        MAX,
    }

    internal class ProgramState
    {
        private PROGRAM_STATE state_;
        private FormState formState_ = null;
        private string name_;

        public delegate void putMessageDele(string msg);
        public event putMessageDele putMessage_;

        private void changeState()
        {
            switch (state_) {
            case PROGRAM_STATE.LOGIN:
                formState_ = new LoginFormState();
                break;

            case PROGRAM_STATE.LOBBY:
                formState_ = new LobbyFormState();
                break;
            }
        }

        public void setState(PROGRAM_STATE state, string ip, uint port)
        {
            if (formState_ != null)
                formState_.close();

            state_ = state;
            this.changeState();
            formState_.open(ip, port);
        }

        public void setName(string name)
        {
            name_ = name;
        }

        public string name()
        {
            return name_;
        }

        public void sendPacket(PacketInterface packet)
        {
            this.formState_.sendPacket(ref packet);
        }

        public void putMessage(string msg)
        {
            putMessage_(msg);
        }

        public void close()
        {
            this.formState_.close();
        }
    }
}