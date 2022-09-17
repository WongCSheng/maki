using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerController : MonoBehaviour
{
    private PlayerMovement controls; //input system, No need do getkeydown as the script, PlayerMovement,
                                     //auto made by the input system, have all the get input stuff.

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

    private GameObject[] objectToPush;

    private void Awake()
    {
        controls = new PlayerMovement(); //idk this... bring input system into this script?
    }

    private void OnEnable()
    {
        controls.Enable(); //enable it.
    }

    private void OnDisable()
    {
        controls.Disable(); //disable it.
    }

    // Start is called before the first frame update
    void Start()
    {
        controls.PlayerMovements.Move.performed += ctx => Move(ctx.ReadValue<Vector2>());

        objectToPush = GameObject.FindGameObjectsWithTag("PushableObjects"); //Find all the gameobjects with that tag
    }

    private void Move(Vector2 direction) //direction values is from input system. 
    {
        if (CanMove(transform.position, direction)) //Player will move if CanMove == true or if pushable object current point is not the same as player.
        {
            transform.position += (Vector3)direction;  //MOVE ME. - Player(2022)
        }
    }

    private bool CanMove(Vector3 position, Vector2 direction) //direction values is Move function. 
    {
        //For pushable objects.
        Vector2 newpos = new Vector2(position.x, position.y) + direction;

        foreach (var pushableObjects in objectToPush)
        {
            if (pushableObjects.transform.position.x == newpos.x && pushableObjects.transform.position.y == newpos.y)
            {
                Push pushObj = pushableObjects.GetComponent<Push>();
                if (pushObj && pushObj.Move(direction))
                {
                    return false;
                }
                else
                {
                    return true; 
                }
            }
        }

        //for walls.
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction); //get the grid Position
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition)) //check if THERE IS NO tile on ground TM or THERE IS a tile on wall TM.
        {
            return false; //you hit a wall, player. STOP RIGHT THERE!
        }
        else 
        { 
            return true; //you didn't hit a wall, player. You are allow to move.
        } 

    }

    // Update is called once per frame
    void Update()
    {

    }
}
