using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerController : MonoBehaviour
{
    private PlayerMovement controls; //input system, No need do getkeydown as the script, PlayerMovement,
                                     //auto made by the input system, have all the get input stuff.

    public static Vector2 playerCurrentPoint;

    [SerializeField]
    private Tilemap groundTilemap; //get the groud Tilemap
    [SerializeField]
    private Tilemap wallTilemap; //get the wall Tilemap

   // private GameObject[] objectToPush;
   // public bool wallinFront;
   // private Vector2 storedVector2d;
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
   
       // objectToPush = GameObject.FindGameObjectsWithTag("PushableObjects"); //Find all the gameobjects with that tag
    }

    private void Move(Vector2 direction) //direction values is from input system. 
    {
        if (CanMove(direction)) //Player will move if CanMove == true
        {
           // storedVector2d = direction;
           // if (!wallinFront)
            transform.position += (Vector3)direction;  //MOVE ME. - Player(2022)

            playerCurrentPoint = transform.position;
         //   Debug.Log(playerCurrentPoint);
        }
    }

    private bool CanMove(Vector2 direction) //direction values is Move function. 
    {

        RaycastHit2D hitObstacles = Physics2D.Raycast(new Vector3(transform.position.x, transform.position.y + 0.5f, transform.position.z), Vector2.up, 5);
      
        //  If it hits something...
        if (hitObstacles.collider != null)
        {
         //   Debug.Log(hitObstacles.collider.gameObject);
           if(hitObstacles.collider.gameObject.GetComponent<Push>() != null)
            {
                Debug.Log("Test");
                hitObstacles.collider.gameObject.GetComponent<Push>().AssignPush();
             
            }
        }

    
       
        Vector3Int gridPosition = groundTilemap.WorldToCell(transform.position + (Vector3)direction); //get the grid Position
        if (!groundTilemap.HasTile(gridPosition) || wallTilemap.HasTile(gridPosition) ||Push.hitWall==true) //check if THERE IS NO tile on ground TM or THERE IS a tile on wall TM.
        {
            return false; //you hit a wall, player. STOP RIGHT THERE!
        }
        else { return true; } //you didn't hit a wall, player. You are allow to move.

    }

    // Update is called once per frame
    void Update()
    {
        Debug.DrawRay(new Vector3(transform.position.x, transform.position.y, transform.position.z), Vector2.up);

     /*   RaycastHit2D hitWalls = Physics2D.Raycast(new Vector3(transform.position.x, transform.position.y + 2f, transform.position.z), Vector2.up, 5);
        //  If it hits something...
        if (hitWalls.collider != null && hitWalls.collider.tag == "Walls")
        {

            Debug.Log(hitWalls.collider.gameObject);
            wallinFront = true;
        }
        else
        {
            wallinFront = false;
        }*/
    }
}
