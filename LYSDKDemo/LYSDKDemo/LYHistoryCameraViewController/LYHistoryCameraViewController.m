//
//  LYHistoryCameraViewController.m
//  LYCloudDemo
//
//  Created by QuinnQiu on 16/1/14.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import "LYHistoryCameraViewController.h"
#import "LYHistoryModel.h"
#import "LYPlayer.h"

#define kScreenWidth [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height
//#define TESTHISTORY_HASH_CID     @"DE1C130061987198"
#define TESTHISTORY_HASH_CID     @"B5990A006298A196"


//#define TESTHISTORY_HASH_CID     @"EAC129007A0F124E"


//#define TESTHISTORY_CID     @"10000412"
#define TESTHISTORY_CID     @"10000025"



//#define TESTHISTORY_CID     @"1003201"

@interface LYHistoryCameraViewController () {
    NSMutableArray *dataSourceArray;
    NSString *StartBeforeThreeDateStr;
    UIButton *changeBtn;
    UIScrollView *listScrollView;
    NSInteger startTime;
    NSInteger endTime;
    NSInteger arrayCount;
    NSMutableArray *copyArray;
    NSString *accessToken;
    LYPlayer *player;
    UIView *playView;
    LYPlayerConfiguration *playerConfig;
}

@end

@implementation LYHistoryCameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initSubviews];
    [self creatChangeBtn];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (void) viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [player close];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void)initSubviews
{
    self.navigationItem.title = @"观看历史";
    player = [[LYPlayer alloc] init];
    
    dataSourceArray = [NSMutableArray array];
    self.view.backgroundColor = [UIColor whiteColor];
    self.view.transform = CGAffineTransformMakeRotation(M_PI_2);
    
    
    //获取今天零点的时间戳
    StartBeforeThreeDateStr = [self getTimerDateString];
    
    startTime = [StartBeforeThreeDateStr integerValue];
    endTime = [StartBeforeThreeDateStr integerValue] + 24 * 60 * 60 * 1;

    [self start:nil];
    //显示view
    listScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(20, kScreenWidth - 70, 400, 0)];
    [self.view addSubview:listScrollView];
    listScrollView.backgroundColor = [UIColor redColor];
    [self.view bringSubviewToFront:listScrollView];
   }

- (void) test: (UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);

        NSString *documentsDirectory = [paths objectAtIndex:0];

        NSString *datasPath = [documentsDirectory stringByAppendingPathComponent:@"test.mp4"];
//        [player startLocalRecordWithPath:datasPath status:^(NSString *errorString, NSInteger statusCode) {
//            NSLog(@"startLocalRecordWithPath statusCode = %zd", statusCode);
//        }];
    } else {
//        [player stopLocalRecordWithBlock:^(NSInteger size, NSInteger time) {
//            NSLog(@"size = %zd, time = %zd", size, time);
//        }];
    }
}

- (void) start: (NSArray *)array {
    [self getRecordSegmentList:array];
    
    NSString *connectURL = [NSString stringWithFormat:@"topvdn://183.57.151.111:1935?protocolType=3&connectType=2&token=%s&cid=%s&begin=%ld&end=%ld&play=%ld", [@"10000025_3356491776_1464767196_d6f7fa9bc0c9cd7182c5f9eec5413981" UTF8String],[@"10000025" UTF8String], startTime, endTime, startTime];
    
    [player open:connectURL openStatus:^(LYstatusCode statusCode, NSString *errorString) {
        
        NSLog(@"errorString = %@, statusCode = %zd", errorString, statusCode);
    } playerStatus:^(NSDictionary *playerMessageDic) {
        
        NSLog(@"dictionary = %@", playerMessageDic);
    }];

    playView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
    [self.view addSubview:playView];
    
    playerConfig = [[LYPlayerConfiguration alloc] initWithPlayView:playView frame:CGRectMake(40, 0, kScreenHeight, kScreenWidth) decodeMode:LYPlayerDecodeModeSoft];
    [player setViewWithConfiguration:playerConfig];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if (changeBtn != nil) {
            
            [self.view bringSubviewToFront:changeBtn];
        }
        
        if (listScrollView != nil) {
            
            [self.view bringSubviewToFront:listScrollView];
        }
    });
    
    
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(200, 200, 100, 50)];
    btn.backgroundColor = [UIColor redColor];
    [self.view addSubview:btn];
    [self.view bringSubviewToFront:btn];
    [btn addTarget:self action:@selector(test:) forControlEvents:UIControlEventTouchUpInside];

}

- (void) play{
    
}

/**
 *  获取今天的时间戳
 *
 *  @return <#return value description#>
 */
-(NSString *)getTimerDateString
{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyy-MM-dd 00:00:00";
    NSDateComponents *dateBeforeDateComponents = [[NSDateComponents alloc] init];
    dateBeforeDateComponents.day = 0;
    NSDate *date = [[NSCalendar currentCalendar] dateByAddingComponents:dateBeforeDateComponents toDate:[NSDate date] options:0];
    NSString *dateStr = [formatter stringFromDate:date];
    
    NSDateFormatter *switchFormatter = [[NSDateFormatter alloc] init];
    NSTimeZone* GTMzone = [NSTimeZone systemTimeZone];
    [switchFormatter setTimeZone:GTMzone];
    switchFormatter.dateFormat = @"yyyy-MM-dd HH:mm:ss";
    NSDate *switchDate = [switchFormatter dateFromString:dateStr];
    NSString *timpStr = [NSString stringWithFormat:@"%ld",(long)[switchDate timeIntervalSince1970]];
    
    return timpStr;
}

/**
 *  根据时间戳来换取时间
 */

-(NSString *)getDateWithTimer:(NSInteger)timer
{
    NSDate *dateildate = [NSDate dateWithTimeIntervalSince1970:(CGFloat)timer];
    NSDateFormatter *form = [[NSDateFormatter alloc] init];
    [form setDateStyle:NSDateFormatterMediumStyle];
    [form setTimeStyle:NSDateFormatterShortStyle];
    [form setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    
    NSString *currect = [form stringFromDate:dateildate];
    
    return currect;
}

-(void)creatChangeBtn
{
    changeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    changeBtn.frame = CGRectMake(20, kScreenWidth - 70, 100, 50);
    changeBtn.backgroundColor = [UIColor blueColor];
    [changeBtn setTitle:@"选择" forState:UIControlStateNormal];
    [self.view addSubview:changeBtn];
    [self.view bringSubviewToFront:changeBtn];
    [changeBtn addTarget:self action:@selector(showHistoryList:) forControlEvents:UIControlEventTouchUpInside];
}

-(void)showHistoryList:(UIButton *)Btn
{
    if (arrayCount == 0) {
        
        return;
    }
    
    Btn.selected = !Btn.selected;
    
    if (Btn.selected) {
        
        CGFloat H = arrayCount * 40;
        CGRect frame = listScrollView.frame;
        
        if (H >= kScreenWidth - 140) {
            
            frame.origin.y = 70;
            frame.size.height = kScreenWidth - 140;
        }else
        {
            frame.origin.y = kScreenWidth - 70 - H;
            frame.size.height = H;
        }
        
        listScrollView.frame = frame;
        
    }else
    {
        CGRect frame = listScrollView.frame;
        frame.size.height = 0;
        frame.origin.y = kScreenWidth - 70;
        listScrollView.frame = frame;
    }
    
}


/**
 *  delegete 此方法可以获取到录像的时间段
 */

- (void)getRecordSegmentList:(NSArray *)p_RecordSegmentList {
    [dataSourceArray removeAllObjects];
    NSLog(@"-----%@- %@",p_RecordSegmentList,[NSThread currentThread]);
    
    if (p_RecordSegmentList.count == 0) {
        
        return;
    }
    
    
    for (NSDictionary *dic in p_RecordSegmentList) {
        
        LYHistoryModel *model = [[LYHistoryModel alloc] init];
        [model setValuesForKeysWithDictionary:dic];
        
        //筛选出大于30min的时间段展示
        if ([model.to integerValue] - [model.from integerValue] >= 30 * 60) {
            
            [dataSourceArray addObject:model];
        }
    }
    
    //   NSInteger Rt = [recordPlayer Play:TESTHISTORY_CID FromTime:startTime ToTime:endTime PlayTime:startTime];
    
//    [iRecordPlayer Play:TESTHISTORY_CID FromTime:startTime ToTime:endTime PlayTime:startTime block:^(NSInteger valueRt) {
//
//    }];
    
    
    BOOL isOn = NO;
    for (UIView *view in listScrollView.subviews) {
        
        if ([view isKindOfClass:[UIButton class]]) {
            
            isOn = YES;
            break;
        }
    }
    
    if (isOn) {
        
        return;
    }
    
    
    for (int i = 0; i < dataSourceArray.count; i++) {
        
        arrayCount = dataSourceArray.count;
        copyArray = [NSMutableArray arrayWithArray:dataSourceArray];
        LYHistoryModel *model = dataSourceArray[i];
        
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.frame = CGRectMake(0, i * 40, listScrollView.bounds.size.width, 40);
        [listScrollView addSubview:btn];
        btn.tag = 1000 + i;
        [btn setTitle:[NSString stringWithFormat:@"%@-%@",[self getDateWithTimer:[model.from integerValue]],[self getDateWithTimer:[model.to integerValue]]] forState:UIControlStateNormal];
        
        [btn addTarget:self action:@selector(changeHistory:) forControlEvents:UIControlEventTouchUpInside];
        
    }
    
    listScrollView.contentSize = CGSizeMake(0, dataSourceArray.count * 40);
    
}

- (void)changeHistory:(UIButton *)btn {
//    [iRecordPlayer Stop];
    NSInteger index = btn.tag - 1000;
    LYHistoryModel *model = copyArray[index];
    
    startTime = [model.from integerValue];
    endTime = [model.to integerValue];
    
//    [iRecordPlayer GetRecordSegmentList:TESTHISTORY_CID from:startTime to:endTime delegate:self];
    
    
    CGRect frame = listScrollView.frame;
    frame.size.height = 0;
    frame.origin.y = kScreenWidth - 70;
    listScrollView.frame = frame;
    changeBtn.selected = NO;
}

@end
