using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class Push1 : MonoBehaviour
{  //private string playerEnterPoint = "";

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

    private GameObject[] objectToPush;

    // Start is called before the first frame update
    void Start()
    {
        objectToPush = GameObject.FindGameObjectsWithTag("PushableObjects"); //Find all the gameobjects with that tag
    }

    // Update is called once per frame
    //void Update()
    /* {
 if (playerEnterPoint == "up")
           {        
                   Vector2 up= new Vector2(0,1);
                   Debug.Log(up);
                   Move(up);
                   playerEnterPoint = " ";
           }


       }
       public void AssignPush()
       {
           Debug.Log("test");
           playerEnterPoint = "up";
       }*/

    public bool Move(Vector2 direction)
    {
        if (CannnotMove(transform.position, direction)) //move if CanMove == true
        {
            return true;
        }
        else
        {
            transform.Translate(direction);
            return false;
        }
    }

    private bool CannnotMove(Vector3 position, Vector2 direction) //Yes is reverse. Headache figuring out from youtube. :D
    {
        Vector2 newpos = new Vector2(position.x, position.y) + direction;

        foreach (var pushableObjects in objectToPush)
        {
            if (pushableObjects.transform.position.x == newpos.x && pushableObjects.transform.position.y == newpos.y)
            {
                return true;
            }
        }

        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction); //get the grid Position
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition)) //check if THERE IS NO tile on ground TM or THERE IS a tile on wall TM.
        {
            return true; //STOP RIGHT THERE!
        }
        else
        {
            return false; //Pushable object(s) may move.
        }
    }

    private void Update()
    {

    }
}
