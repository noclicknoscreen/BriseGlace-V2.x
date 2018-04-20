using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Quobject.SocketIoClientDotNet.Client;
using Newtonsoft.Json;

public class Players {
	public Player[] players;
}
public class Player {
	
	public string 	ip;
	public int		nr;
	public string	socketId;
	public bool		isAvailable;
	public string	lastMessage;
	public Message[]	messages;
};

public class Message {
	public string time;
	public string text;
};


public class SocketIOScript : MonoBehaviour {
	public string serverURL;

	public InputField uiInput = null;
	public Button uiSend = null;
	public Text uiChatLog = null;

	protected Socket socket = null;
	protected List<string> chatLog = new List<string> (); 

	void Destroy() {
		DoClose ();
	}

	// Use this for initialization
	void Start () {
		DoOpen ();

		uiSend.onClick.AddListener(() => {
			SendChat(uiInput.text);
			uiInput.text = "";
			uiInput.ActivateInputField();
		});
	}
	
	// Update is called once per frame
	void Update () {
		lock (chatLog) {
			if (chatLog.Count > 0) {
				string str = uiChatLog.text;
				foreach (var s in chatLog) {
					str = str + "\n" + s;
				}
				uiChatLog.text = str;
				chatLog.Clear ();
			}
		}
	}

	void DoOpen() {
		if (socket == null) {
			socket = IO.Socket (serverURL);
			socket.On (Socket.EVENT_CONNECT, () => {
				lock(chatLog) {
					// Access to Unity UI is not allowed in a background thread, so let's put into a shared variable
					chatLog.Add("Socket.IO connected.");
				}
			});

			socket.On ("players", (data) => {

				string str = data.ToString();

				Debug.Log("Players received.");
				//Debug.Log(str);

				Players players = JsonConvert.DeserializeObject<Players> (str);
				foreach(Player onePlayer in players.players)
				{
					Debug.Log(onePlayer.ip);
				}
//				string strChatLog = "user#" + chat.id + ": " + chat.msg;
//
//				// Access to Unity UI is not allowed in a background thread, so let's put into a shared variable
//				lock(chatLog) {
//					chatLog.Add(strChatLog);
//				}
			});
		}
	}

	

	void DoClose() {
		if (socket != null) {
			socket.Disconnect ();
			socket = null;
		}
	}

	void SendChat(string str) {
		if (socket != null) {
			socket.Emit ("chat", str);
		}
	}
}
