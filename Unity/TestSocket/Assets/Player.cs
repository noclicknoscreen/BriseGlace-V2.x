using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

	private bool 	isAvailable;
	private string 	message;
	private float 	volume;

	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
		try{

			GameObject myText = this.transform.Find("Text").gameObject;
			GameObject myIconAvailable = this.transform.Find("IconAvailable").gameObject;
			GameObject myIconNotAvailable = this.transform.Find("IconNotAvailable").gameObject;
			GameObject myVolumeMarker = this.transform.Find("VolumeMarker").gameObject;

			if (myText == null || myIconAvailable == null || myIconNotAvailable == null) {
				Debug.LogError (this.ToString() + " : Objects not found : unable to update");

			}else{
				myIconAvailable.GetComponent<Renderer> ().enabled = isAvailable;
				myIconNotAvailable.GetComponent<Renderer> ().enabled = !isAvailable;
				myText.GetComponent<TextMesh> ().text = message;

				Vector3 thisScale;
//				if(isAvailable){
					float myScale = Mathf.Lerp(1.0F, 10.0F, volume);
					thisScale = new Vector3(myScale, myScale, myScale);
//				}else{
//					thisScale = new Vector3(1.0F, 1.0F, 1.0F);
//				}
				myVolumeMarker.transform.localScale = thisScale;
			}
		}
		catch (System.Exception e)
		{
			Debug.LogException(e, this);
		}
	}

	public void setAvailable(bool _available){
		//Debug.Log ("Is available received : " + _available);
		this.isAvailable = _available;
	}
	public void setMessage(string _message){
		//Debug.Log ("Message received : " + _message);
		this.message = _message;
	}
	public void setVolume(float _volume){
		//Debug.Log ("Message received : " + _message);
		this.volume = 0.5f * _volume + 0.5f * this.volume;
	}
}
