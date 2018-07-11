using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace DummyClient
{
    public class JSUnityNet
    {
        private Network network_;

        public JSUnityNet()
        {
            if (network_ == null)
                network_ = new Network();

            network_.setPacketProcess(new LoginPacketProcess());
        }

        public bool ConnectUnityNet(string ip, uint port)
        {
            return network_.connect(ip, port);
        }

        public void CloseUnityNet()
        {
            if (network_ != null)
                network_.disConnect();
        }

        public void SendLoginPacket(string id, string pw)
        {
            PK_C_REQ_ID_PW packet = new PK_C_REQ_ID_PW();
            packet.id_ = id;
            packet.password_ = pw;
            network_.sendPacket(packet);
        }
    }
}

public class BtnClick : MonoBehaviour
{
    public int count = 0;

    public static string id_str;
    public static string pw_str;

    DummyClient.JSUnityNet js_unity_net;

    public void Start()
    {
        if (js_unity_net == null)
            js_unity_net = new DummyClient.JSUnityNet();

        if (js_unity_net.ConnectUnityNet("127.0.0.1", 9000))
            Debug.Log("Server Connect Succeed");
    }

    public void Update()
    {
    }

    public void OnClick()
    {
        count++;
        Debug.Log(id_str + ", " + pw_str);

        js_unity_net.SendLoginPacket(id_str, pw_str);
    }

    public void OnClickDisconnect()
    {
        js_unity_net.CloseUnityNet();

        Debug.Log("Server Disconnect");
    }

    public void OnChange(string new_str)
    {
        if (tag == "ID")
        {
            id_str = new_str;
            Debug.Log("id : " + id_str);
        }
        else if (tag == "PW")
        {
            pw_str = new_str;
            Debug.Log("pw : " + pw_str);
        }
    }
}
