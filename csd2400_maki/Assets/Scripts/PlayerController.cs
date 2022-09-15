using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float moveSpeed = 5f; //player movement speed
    public Transform movePoint; //point of player move

    public LayerMask whatStopMovements;

    // Start is called before the first frame update
    void Start()
    {
        movePoint.parent = null; //movePoint no more parent using script
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = Vector3.MoveTowards(transform.position, movePoint.position, moveSpeed * Time.deltaTime);

        if (Vector3.Distance(transform.position, movePoint.position) <= 0.05f)//if player moves,
        {
            if (Mathf.Abs(Input.GetAxisRaw("Horizontal")) == 1f) //Mathf.Abs doesnt care of value is postive or negative. It only change the number, thus, it's only checking the value 1f.
            {
                if (!Physics2D.OverlapCircle(movePoint.position + new Vector3(Input.GetAxisRaw("Horizontal"), 0f, 0f), 0.2f, whatStopMovements)) //draw a cricle to check if there's a colliders on that layermask, if no,
                { 
                    movePoint.position += new Vector3(Input.GetAxisRaw("Horizontal"), 0f, 0f); 
                }
            }

            if (Mathf.Abs(Input.GetAxisRaw("Vertical")) == 1f) //Mathf.Abs doesnt care of value is postive or negative. It only change the number, thus, it's only checking the value 1f.
            {
                if (!Physics2D.OverlapCircle(movePoint.position + new Vector3(0f, Input.GetAxisRaw("Vertical"), 0f), 0.2f, whatStopMovements)) //draw a cricle to check if there's a colliders on that layermask, if no,
                {
                    movePoint.position += new Vector3(0f, Input.GetAxisRaw("Vertical"), 0f);
                }
            }
        }
    }
}
