package main

import (
	"database/sql"
	"encoding/base64"
	"fmt"
	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
	uuid "github.com/satori/go.uuid"
	"strconv"
)

// 维护一个棋盘
var (
	chess     [30][30]int
	black     bool
	white     bool
	begin     bool
	flag      int
	blackuser string
	whiteuser string
	blackmac  string
	whitemac  string
	blacktime string
	whitetime string
)

// 清理棋盘，初始化黑白双方
func cleanChess() {
	for i := 0; i < 30; i++ {
		for j := 0; j < 30; j++ {
			chess[i][j] = 0
		}
	}
	flag = 1
	begin = false
	black = false
	white = false
}

var Db *sql.DB
var err error

// 初始化数据库
func sqlInit() {
	Db, err = sql.Open("mysql", "root:password@tcp(127.0.0.1:3306)/test")
	if err != nil {
		fmt.Println(err)
	}
	err = Db.Ping()
	if err != nil {
		fmt.Println(err)
	}
}

// 增
func addUser(mac string, username string) bool {
	sqlstr := "insert into users(mac,username) values (?,?)"

	_, err2 := Db.Exec(sqlstr, mac, username)
	if err2 != nil {
		fmt.Println(err2)
		return false
	}
	return true
}

// 查
func selectUser(mac string) (string, error) {
	sqlstr := "select username from users where mac =?"
	row, err2 := Db.Query(sqlstr, mac)
	if err2 != nil {
		fmt.Println(err2)
		return "", err2
	}
	row.Next()
	var username string
	err1 := row.Scan(&username)
	if err1 != nil {
		fmt.Println(err1)
		return "", err1
	}
	return username, nil
}

// 改
func updateUser(mac string, username string) bool {
	sqlstr := "UPDATE users SET username=? WHERE mac=?;"
	_, err1 := Db.Exec(sqlstr, username, mac)
	if err1 != nil {
		fmt.Println(err1)
		return false
	}
	return true
}

// 查询是否注册账号以及name值 mac
func find(c *gin.Context) {
	mac := c.Query("mac")
	mac = base64.StdEncoding.EncodeToString([]byte(mac))

	name, err1 := selectUser(mac)

	if err1 != nil {
		c.JSON(404, "not found")
		return
	} else {
		bytemac, _ := base64.StdEncoding.DecodeString(mac)
		mac = string(bytemac)

		bytename, _ := base64.StdEncoding.DecodeString(name)
		name = string(bytename)
		c.JSON(200, gin.H{
			"mac":  mac,
			"name": name,
		})
	}
}

// 为机器注册账号 mac name
func register(c *gin.Context) {
	if len(c.Query("mac")) > 50 {
		c.JSON(404, "false")
		return
	}
	if len(c.Query("name")) > 40 {
		c.JSON(404, "false")
		return
	}
	name := c.DefaultQuery("name", uuid.NewV4().String())
	mac := c.Query("mac")
	mac = base64.StdEncoding.EncodeToString([]byte(mac))
	name = base64.StdEncoding.EncodeToString([]byte(name))

	success := addUser(mac, name)

	bytemac, _ := base64.StdEncoding.DecodeString(mac)
	bytename, _ := base64.StdEncoding.DecodeString(name)
	mac = string(bytemac)
	name = string(bytename)
	if success {
		c.JSON(200, gin.H{
			"mac":  mac,
			"name": name,
		})
	} else {
		c.JSON(502, "error")
	}
}

// 改变name mac name
func rename(c *gin.Context) {
	if len(c.Query("mac")) > 30 {
		c.JSON(404, "false")
		return
	}
	if len(c.Query("name")) > 40 {
		c.JSON(404, "false")
		return
	}

	name := c.DefaultQuery("name", uuid.NewV4().String())
	mac := c.Query("mac")
	mac = base64.StdEncoding.EncodeToString([]byte(mac))
	name = base64.StdEncoding.EncodeToString([]byte(name))

	success := updateUser(mac, name)

	bytemac, _ := base64.StdEncoding.DecodeString(mac)
	bytename, _ := base64.StdEncoding.DecodeString(name)
	mac = string(bytemac)
	name = string(bytename)
	if success {
		c.JSON(200, gin.H{
			"mac":  mac,
			"name": name,
		})
	} else {
		c.JSON(404, "error")
	}
}

// 进入等待环节 mac color
func wait(c *gin.Context) {
	mac := c.Query("mac")
	if white && black {
		c.JSON(502, "bad request") //棋局已开始，是否观战
		return
	}
	color := c.Query("color")
	mac = base64.StdEncoding.EncodeToString([]byte(mac))

	name, err1 := selectUser(mac)

	if err1 != nil {
		c.JSON(404, "not found") //未注册
		return
	}

	bytemac, _ := base64.StdEncoding.DecodeString(mac)
	bytename, _ := base64.StdEncoding.DecodeString(name)
	mac = string(bytemac)
	name = string(bytename)

	if color == "black" {
		if black {
			c.JSON(502, "wrong") //座位已被占
			return
		} else {
			black = true
			blackuser = name
			blackmac = mac
			start := isbegin()
			if start {
				c.JSON(200, "begin") //开始游戏
			} else {
				c.JSON(200, "wait") //等待对手进入
			}
		}
	} else if color == "white" {
		if white {
			c.JSON(502, "wrong") //座位已被占
			return
		} else {
			white = true
			whiteuser = name
			whitemac = mac
			start := isbegin()
			if start {
				c.JSON(200, "begin") //开始游戏
			} else {
				c.JSON(200, "wait") //等待对手进入
			}
		}
	} else {
		c.JSON(404, "color error") //颜色输入错误
	}
}

// 退出棋盘 mac
func exit(c *gin.Context) {
	mac := c.Query("mac")
	mac = base64.StdEncoding.EncodeToString([]byte(mac))

	name, err1 := selectUser(mac)

	if err1 != nil {
		c.JSON(404, "not found") //未注册
		return
	}

	bytemac, _ := base64.StdEncoding.DecodeString(mac)
	bytename, _ := base64.StdEncoding.DecodeString(name)
	mac = string(bytemac)
	name = string(bytename)

	if mac == blackmac && name == blackuser {
		cleanChess()
		begin = false
		black = false
		white = false
		c.JSON(200, "success") //成功退出
	} else if mac == whitemac && name == whiteuser {
		cleanChess()
		begin = false
		black = false
		white = false
		c.JSON(200, "success") //成功退出
	} else {
		c.JSON(502, "bad request") //你都没玩退什么
	}
}

// 上传步骤 mac h l value
func up(c *gin.Context) {
	mac := c.Query("mac")
	if !white && !black {
		c.JSON(502, "bad request") //棋局还没开始
		return
	}
	mac = base64.StdEncoding.EncodeToString([]byte(mac))
	name, err1 := selectUser(mac)
	if err1 != nil {
		c.JSON(404, "not found") //未注册
		return
	}
	bytemac, _ := base64.StdEncoding.DecodeString(mac)
	bytename, _ := base64.StdEncoding.DecodeString(name)
	mac = string(bytemac)
	name = string(bytename)

	if (name != whiteuser || mac != whitemac) && (name != blackuser || mac != blackmac) {
		c.JSON(502, "p") //你没玩你传个p
		return
	}

	if mac == whitemac {
		if flag == 1 {
			c.JSON(502, "e") //咋一直是你走
			return
		}
	} else {
		if flag == 2 {
			c.JSON(502, "e") //咋一直是你走
			return
		}
	}

	h, err := strconv.Atoi(c.Query("h"))
	if err != nil || h < 0 || h > 29 {
		c.JSON(502, "error") //参数错误
		return
	}
	l, err := strconv.Atoi(c.Query("l"))
	if err != nil || l < 0 || l > 29 {
		c.JSON(502, "error") //参数错误
		return
	}
	if chess[h][l] != 0 {
		c.JSON(502, "err") //放置棋子处已经被占用
		return
	}
	chess[h][l], err = strconv.Atoi(c.Query("value"))
	if err != nil {
		c.JSON(502, "error") //参数错误
		return
	}
	c.JSON(200, "ok")
	if flag == 1 {
		flag = 2
	} else {
		flag = 1
	}
}

// 是否开始
func isbegin() bool {
	if white && black {
		begin = true
	} else {
		begin = false
	}
	return begin
}

//定时计划

func main() {
	r := gin.Default()
	cleanChess()
	sqlInit()
	r.GET("/find", find)         //通过mac查name
	r.GET("/register", register) //注册name
	r.GET("/rename", rename)     //更改name

	r.GET("/wait", wait) //进入游戏
	r.GET("/exit", exit) //退出棋局

	r.GET("/up", up) //上传步骤

	r.GET("/reset", func(c *gin.Context) {
		cleanChess()
		begin = false
		black = false
		white = false
		c.JSON(200, "success") //成功退出
	})
	r.GET("/update", func(c *gin.Context) {
		if begin == false {
			c.JSON(502, "bad request") //游戏未开始或对方逃跑
			return
		}
		c.JSON(200, gin.H{
			"chess": chess,
		})
	})
	r.Run(":1211")
}
