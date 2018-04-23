using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Quobject.SocketIoClientDotNet.Client;
using Newtonsoft.Json;

public class dataPlayers {
	public dataPlayer[] players;
};

public class dataPlayer {
	
	public string 	ip;
	public int		nr;
	public string	socketId;
	public bool		isAvailable;
	public string	lastMessage;
	public dataMessage[]	messages;
};

public class dataMessage {
	public string time;
	public string text;
};

public class dataVolume{
	public int nr;
	public float volume;
};

public class SocketIOScript : MonoBehaviour {
	public string serverURL;

	public Text uiLog = null;
	public Player P1 = null;
	public Player P2 = null;
	public Player P3 = null;
	public Player[] Players = null;

	protected Socket socket = null;
	protected List<string> logList = new List<string> (); 

	void Destroy() {
		DoClose ();
	}

	// Use this for initialization
	void Start () {
		DoOpen ();
	}
	
	// Update is called once per frame
	void Update () {
		lock (logList) {
			if (logList.Count > 0) {
				string str = uiLog.text;
				foreach (var s in logList) {
					str = str + "\n" + s;
				}
				uiLog.text = str;
				logList.Clear ();
			}
		}
	}

	void DoOpen() {
		if (socket == null) {
			socket = IO.Socket (serverURL);
			socket.On (Socket.EVENT_CONNECT, () => {
				lock(logList) {
					// Access to Unity UI is not allowed in a background thread, so let's put into a shared variable
					logList.Add("Socket.IO connected.");
				}
			});

			socket.On ("players", (data) => {
				string str = data.ToString();

				dataPlayers players = JsonConvert.DeserializeObject<dataPlayers> (str);
				foreach(dataPlayer onePlayer in players.players)
				{
					Debug.Log(onePlayer.nr + ":" + onePlayer.ip 
						+ " [LastMessage:" + onePlayer.lastMessage +"]" 
						+ " [isAvailable:" + onePlayer.isAvailable +"]");
					updatePlayer(onePlayer);
				}

			});

			socket.On ("volume", (data) => {
				//string str = data.ToString();
				//Debug.Log("Volume data : " + str);
				dataVolume volume = JsonConvert.DeserializeObject<dataVolume> (data.ToString());
				updateVolume(volume.nr, volume.volume);
			});

		}
	}

	Player getPlayer (int nr)
	{
		Player playerToUpdate = null;
		switch (nr) {
		case 1:
			playerToUpdate = P1;
			break;
		case 2:
			playerToUpdate = P2;
			break;
		case 3:
			playerToUpdate = P3;
			break;
		default:
			Debug.Log ("Player number not available : " + nr);
			break;
		}
		return playerToUpdate;
	}

	private void updateVolume(int playerNum, float playerVolume){
		var playerToUpdate = getPlayer (playerNum);

		if (playerToUpdate != null) {
			playerToUpdate.setVolume (playerVolume);
		};
	}

	private void updatePlayer(dataPlayer dtPlayer){

		var playerToUpdate = getPlayer (dtPlayer.nr);

		if (playerToUpdate != null) {
			playerToUpdate.setMessage (dtPlayer.lastMessage);
			playerToUpdate.setAvailable (dtPlayer.isAvailable);
		};

	}

	void DoClose() {
		if (socket != null) {
			socket.Disconnect ();
			socket = null;
		}
	}

}
