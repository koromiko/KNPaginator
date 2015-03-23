//
//  KNPaginator.h
//  Neo
//
//  Created by Neo on 4/26/14.
//  Copyright (c) 2014 Neo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KNPaginator;

@protocol KEPaginatorDatasource <NSObject>



/**
 *  Datasource provides callback with an array of data, which will be appended to current data array.
 *
 *  @param paginator     current data array
 *  @param completeBlock call this block when a set of data is fetched
 *  @param failBlock     the paginator would stop if fail block is called
 */
- (void)fetchDataForPaginator:(KNPaginator*)paginator withComplete:(void (^)(NSArray *dataArray))completeBlock fail:(void (^)(NSError *error))failBlock;



@optional

/**
 *  Datasource provides callback with an array of data, which will be prepended to current data array.
 *
 *  @param paginator      current data array
 *  @param completeBlock call this block when a set of data is fetched
 *  @param failBlock     the paginator would stop if fail block is called
 */
- (void)fetchNewDataForPaginator:(KNPaginator*)paginator withComplete:(void (^)(NSArray *dataArray))completeBlock fail:(void (^)(NSError *error))failBlock;


/**
 *  The number of per fetch.
 *
 *  @return number of data
 */
- (NSInteger)numberOfItemsPerFetch;

@end

@protocol KEPaginatorDelegate <NSObject>

/**
 *  Finished fetch a bunch of data
 *
 *  @param paginator    current data array
 *  @param idx          the data index in the data array to which data added
 *  @param numberOfData the number of data in this fetch
 */
- (void)paginator:(KNPaginator*)paginator didAppendDataToIndex:(NSInteger)idx withNumberOfData:(NSInteger)numberOfData;


@optional

/**
 *  Finished fetch a bunch of data
 *
 *  @param paginator    current data array
 *  @param idx          the data index in the data array to which data added
 *  @param numberOfData the number of data in this fetch
 */
- (void)paginator:(KNPaginator*)paginator didPreppendDataWithNumberOfData:(NSInteger)numberOfData;

/**
 *  the paginator did fetch the last data, called only when data source numberOfItemsPerFetch implemented
 *
 *  @param paginator current data array
 */
- (void)paginatorDidFetchTheLastObject:(KNPaginator*)paginator;

@end



@interface KNPaginator : NSObject


@property (nonatomic, strong) NSMutableArray *dataArray;

@property (nonatomic, strong) NSArray *tmpDataArray;

@property (nonatomic, weak) id<KEPaginatorDatasource> datasource;
@property (nonatomic, weak) id<KEPaginatorDelegate> delegate;

/**
 *  string for distinquishing paginator
 */
@property (nonatomic, strong) id tagString;

/**
 *  return YES of the last object is fetched
 */
@property (nonatomic) BOOL isFinishedLoadedLastObject;

/**
 *  clear the array
 */
- (void)clearData;

/**
 *  begin to fetch the older data
 */
- (void)nextPage;

/**
 *  begin to fethc the newer data
 */
- (void)fetchNew;


/**
 *  reload data
 */
- (void)reloadData;


/**
 *  number of data in the data array
 *
 *  @return 
 */
- (NSUInteger)count;


/**
 *  get the object at <index> amoung the data array
 *
 *  @param index
 *
 *  @return
 */
- (id)objectAtIndex:(NSUInteger)index;


- (id)lastObject;

- (id)firstObject;



@end
